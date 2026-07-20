// LeetCode 167 - Two Sum II - Input Array Is Sorted
// 难度: Medium / Easy+
// 提交日期: 2026-07-20
// 解法: 双指针·双向对撞剪枝型 (Two Pointers - Opposite Collision)
// 时间复杂度: O(n) - 最坏情况下仅需单次双向指针收敛扫描
// 空间复杂度: O(1) - 原地双向指针逼近，无任何堆内存分配开销 (Zero Allocation)
//
// ==========================================
// 核心系统设计与性能思考 (AI Infra 视角):
// ==========================================
// 1. 数组有序性带来的空间维度剪枝 (Spatial Search Space Pruning):
//    与 001 题不同（001 题无序，只能牺牲空间开辟哈希表维持 O(N)），167 题利用“数组严格单调递增”这一物理特性。
//    当 `nums[left] + nums[right] > target` 时，当前 `right` 指向的最大值与任意剩余元素的和必然大于 `target`，
//    因此单次 `right--` 步进本质上干掉了整整一列无效组合，将 O(N^2) 的二维遍历降维至 O(N) 的单条路径收敛。
//
// 2. 避免哈希离散指针跳转与 Cache Miss (Cache-Friendly Boundary Convergence):
//    彻底放弃 `std::unordered_map`。对撞指针完全作用于 `std::vector` 的连续物理内存块段。
//    随着 `left` 正向递增和 `right` 逆向递减，CPU L1/L2 缓存预取器（Prefetcher）能精准命中连续内存，指令流水线零阻塞。
//
// 3. 边界逻辑防御与无符号类型安全 (Unsigned Underflow Prevention):
//    对 `numbers.size()` 做了有符号类型与空容器边界检查。
//    若未正确处理无符号类型 `size_t`，当容器为空时直接 `- 1` 会触发数值下溢（Underflow），
//    导致 `right` 变为超大正数（18446744073709551615），进而引发严重的段错误（Segmentation Fault）。
//
// ==========================================
// 关键物理内存指针流转图示 (输入: numbers = [2, 7, 11, 15], target = 26):
// ==========================================
// 初始状态: [2,   7,  11,  15], target = 26
//           L              R       (left=0, right=3. sum = 2 + 15 = 17 < 26 -> 和偏小，排除 2，left++)
//
// 状态转移: [2,   7,  11,  15]
//                L         R       (left=1, right=3. sum = 7 + 15 = 22 < 26 -> 和偏小，排除 7，left++)
//
// 命中状态: [2,   7,  11,  15]
//                         L    R   (left=2, right=3. sum = 11 + 15 = 26 == 26 -> 匹配成功！)
//
// 返回结果: [3, 4]                 (题目要求基于 1 的索引，即 {left + 1, right + 1})
// ==========================================

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <limits>

class Solution {
public:
    std::vector<int> twoSum(const std::vector<int>& numbers, int target) {
        if (numbers.size() < 2) {
            return { -1, -1 };
        }
        int left = 0;
        int right = static_cast<int>(numbers.size()) - 1; 

        while (left < right) {
            int sum = numbers[left] + numbers[right];

            if (sum == target) {
                return { left + 1, right + 1 };
            }
            else if (sum < target) {
                ++left;
            }
            else {
                --right;
            }
        }
        return { -1, -1 };
    }
};

// ==========================================
// 本地 Debug 测试入口 (展示工程完备性)
// ==========================================
int main() {
    Solution solver;

    int target = 0;
    std::cout << "请输入目标值 target: ";
    std::cin >> target;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "请输入严格递增有序数组元素（空格隔开，按回车结束）: ";
    std::string line;
    std::getline(std::cin, line);

    std::vector<int> numbers;
    std::stringstream ss(line);
    int num;
    while (ss >> num) {
        numbers.push_back(num);
    }

    std::vector<int> result = solver.twoSum(numbers, target);

    if (result.size() == 2 && result[0] != -1) {
        std::cout << "匹配到的 1-based 索引: [" << result[0] << ", " << result[1] << "]" << std::endl;
        std::cout << "对应物理数值: [" << numbers[result[0] - 1] << ", " << numbers[result[1] - 1] << "]" << std::endl;
    }
    else {
        std::cout << "未找到符合条件的目标对: []" << std::endl;
    }

    return 0;
}
//如果不仅存在唯一解
/*找到一组解后不 return，继续收缩寻找下一组
if (sum == target) {
    results.push_back({ left + 1, right + 1 });
    ++left;
    --right;
}
else if (sum < target) {
    ++left;
}
else {
    --right;
}
*/