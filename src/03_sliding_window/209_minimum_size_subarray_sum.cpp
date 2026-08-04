// LeetCode 209 - Minimum Size Subarray Sum
// 难度: Medium
// 提交日期: 2026-08-04
// 解法: 变长滑动窗口（求最小值双指针收缩）
// 时间复杂度: O(n) - 左右指针至多遍历数组两次
// 空间复杂度: O(1) - 原地双指针，Zero Dynamic Allocation
//
// ==========================================
// 核心系统设计与性能思考 (AI Infra 视角):
// ==========================================
// 1. 贪心收缩策略 (Aggressive Shrink Loop):
//    右指针扩大窗口累加 sum，一旦满足 sum >= target，立即启动内层 while 循环收缩左指针。
//    保证每次更新 min_len 时的窗口都是“以当前 right 为结尾的最短合法子数组”。
//
// 2. 内存与缓存友好 (Zero-Allocation & Cache Locality):
//    仅通过双指针 + 单个累加器在连续内存（std::vector）上单向滑动，
//    具备极佳的 CPU L1/L2 Cache 预取（Prefetching）特性，零动态内存分配开销。
// ==========================================

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

class Solution {
public:
    int minSubArrayLen(int target, const std::vector<int>& nums) {
        const int n = static_cast<int>(nums.size());
        int min_len = INT_MAX;
        int sum = 0;
        int left = 0;

        for (int right = 0; right < n; ++right) {
            sum += nums[right];

            while (sum >= target) {
                min_len = std::min(min_len, right - left + 1);
                sum -= nums[left];
                ++left;
            }
        }

        return min_len == INT_MAX ? 0 : min_len;
    }
};

// ==========================================
// 本地 Debug 测试入口
// ==========================================
int main() {
    Solution solution;
    int target = 0;
    int n = 0;

    std::cout << "请输入 target 值: ";
    if (!(std::cin >> target)) return 0;

    std::cout << "请输入数组元素个数 n: ";
    if (!(std::cin >> n) || n <= 0) return 0;

    std::vector<int> nums(n);
    std::cout << "请输入 " << n << " 个数组元素 (空格分隔): ";
    for (int i = 0; i < n; ++i) {
        std::cin >> nums[i];
    }

    int result = solution.minSubArrayLen(target, nums);

    std::cout << "\n--- 计算结果 ---" << std::endl;
    std::cout << "最小子数组长度: " << result << std::endl;
    std::cout << "----------------------" << std::endl;

    return 0;
}