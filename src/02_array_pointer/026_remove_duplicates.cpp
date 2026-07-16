// LeetCode 026 - Remove Duplicates from Sorted Array
// 难度: Easy
// 提交日期: 2026-07-16
// 解法: 双指针·快慢指针型 (Two Pointers - Fast/Slow)
// 时间复杂度: O(n) - 仅需单次遍历数组
// 空间复杂度: O(1) - 原地修改，无额外内存分配开销
//
// ==========================================
// 核心系统设计与性能思考 (AI Infra 视角):
// ==========================================
// 1. 内存连续性 (Cache Locality):
//    std::vector 在内存中是一块连续的物理空间。采用双指针原地修改（In-place）直接利用了
//    这一特性。相比于分配新数组，原地覆盖写入避免了 Cache Miss，最大化压榨了 CPU 高速缓存。
//
// 2. 规避动态内存申请 (No Dynamic Allocation):
//    如果使用 Python 的 pop() 或 C++ 的 vector.erase()，会导致数组后续元素发生物理搬移，
//    最坏情况下会有 O(n^2) 的时间开销与频繁的内存重分配（Reallocation）。
//    本算法通过指针覆盖（nums[slow] = nums[fast]）消灭了任何形式的动态内存缩容开销。
//
// 3. 引用传递 (Pass by Reference):
//    参数采用 `std::vector<int>& nums` 非只读引用。直接操作调用方的内存，零拷贝。
//
// ==========================================
// 关键物理内存指针流转图示:
// ==========================================
// 初始状态: [1,  1,  2]
//           s   f       (slow 指向 1, fast 扫到第二个 1，相同，fast 前进)
//
// 状态转移: [1,  1,  2]
//           s       f   (fast 扫到 2，与 slow 不同 -> slow 前进一步，覆盖写入)
//
// 写入后:   [1,  2,  2]
//               s   f   (返回长度为 slow + 1 = 2，即有效区域为 [1, 2])
//
// ==========================================

#include <iostream>
#include <vector>

class Solution {
public:
    int removeDuplicates(std::vector<int>& nums) {
        if (nums.empty()) {
            return 0;
        }

        int slow = 0;

        for (int fast = 1; fast < nums.size(); ++fast) {
            // 当快指针遇到了一个与慢指针不同的新元素
            if (nums[fast] != nums[slow]) {
                slow++;
                nums[slow] = nums[fast]; // 原地覆盖写入
            }
        }

        return slow + 1;
    }
};

// ==========================================
// 本地 Debug 测试入口 (展示工程完备性)
// ==========================================
int main() {
    Solution solver;
    std::vector<int> test_case = {1, 1, 2, 2, 3};
    
    std::cout << "Original array size: " << test_case.size() << std::endl;
    
    int new_length = solver.removeDuplicates(test_case);
    
    std::cout << "New length after deduplication: " << new_length << std::endl;
    std::cout << "Modified array prefix: ";
    for (int i = 0; i < new_length; ++i) {
        std::cout << test_case[i] << " ";
    }
    std::cout << std::endl;
    
    return 0;
}
