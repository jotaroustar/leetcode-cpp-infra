// LeetCode 027 - Remove Element
// 难度: Easy
// 提交日期: 2026-07-18
// 解法: 双指针·快慢指针分离型 (Two Pointers - Fast/Slow)
// 时间复杂度: O(n) - 仅需单次扫描
// 空间复杂度: O(1) - 原地修改，无额外内存分配开销
//
// ==========================================
// 核心系统设计与性能思考 (AI Infra 视角):
// ==========================================
// 1. 缓存局部性与写屏障 (Cache Friendliness & Store Op):
//    与 026 题不同，026 是比较 nums[fast] 与 nums[slow]（前后元素对比），
//    而 027 是比较 nums[fast] 与固定值 val。
//    只有当 nums[fast] != val 时才触发写入。如果数组中不含 val，
//    该算法退化为纯顺序写，对 CPU 空间局部性（Spatial Locality）和硬件预取（Hardware Prefetch）极度友好。
//
// 2. 规避 O(n^2) 的数组塌陷 (Avoid Vector Collapse):
//    若直接使用 std::vector::erase()，底层会导致被删元素后面的所有内存块发生物理拷贝（memmove）。
//    本算法通过双指针覆盖，将“元素删除”抽象为“非目标元素的向前紧凑化覆盖”，彻底消灭了内存重分配。
//
// 3. 引用传递与生命周期 (Zero-Copy):
//    参数 `std::vector<int>& nums` 保持零拷贝的高效传递，直接原地修改调用方的堆内存空间。
//
// ==========================================
// 关键物理内存指针流转图示 (输入: [3, 2, 2, 3], val = 3):
// ==========================================
// 初始状态: [3,  2,  2,  3]
//           s
//           f                 (slow=0, fast=0。nums[f] == 3, 触发过滤，fast 前进)
//
// 状态转移: [3,  2,  2,  3]
//           s    f            (nums[f] == 2 != 3 -> nums[s] = nums[f], s++, f++)
//
// 覆盖后:   [2,  2,  2,  3]
//                s   f        (nums[f] == 2 != 3 -> nums[s] = nums[f], s++, f++)
//
// 最终状态: [2,  2,  2,  3]
//                    s   f    (nums[f] == 3, 过滤；遍历结束。返回 slow 长度为 2)
//
// ==========================================

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
class Solution {
public:
    int removeElement(std::vector<int>& nums, int val) {
        int slow = 0;

        for (int fast = 0; fast < nums.size(); ++fast) {
            // 当快指针扫描到不需要被移除的元素时
            if (nums[fast] != val) {
                nums[slow] = nums[fast]; // 原地覆盖写入
                slow++;
            }
        }

        // slow 的值恰好就是新数组的长度
        return slow;
    }
};

// ==========================================
// 本地 Debug 测试入口 (展示工程完备性)
// ==========================================
int main() {
    Solution solver;

    int target_val = 0;
    std::cout << "请输入要移除的目标值 target_val: ";
    std::cin >> target_val;

    // 清除输入缓冲区的换行符，确保后面能正常读取整行
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "请输入数组元素（空格隔开，按回车结束）: ";
    std::string line;
    std::getline(std::cin, line);

    // 解析输入的动态数组
    std::vector<int> test_case;
    std::stringstream ss(line);
    int num;
    while (ss >> num) {
        test_case.push_back(num);
    }

    int new_length = solver.removeElement(test_case, target_val);

    std::cout << new_length << std::endl;
    for (int i = 0; i < new_length; ++i) {
        std::cout << test_case[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}