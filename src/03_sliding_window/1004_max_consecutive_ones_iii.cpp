// LeetCode 1004 - Max Consecutive Ones III
// 难度: Medium
// 提交日期: 2026-08-06
// 解法: 变长滑动窗口（预算容忍度机制）
// 时间复杂度: O(N) - 左右指针至多遍历数组一次
// 空间复杂度: O(1) - 原地双指针，Zero Dynamic Allocation
//
// ==========================================
// 核心系统设计与性能思考 (AI Infra 视角):
// ==========================================
// 1. 问题模型等价转换 (Problem Model Transformation):
//    将"至多翻转 K 个 0"转化为"窗口内 0 的数量 zero_count <= k"。
//    避免显式修改数组元素，维持原本数据的 Read-Only 属性。
//
// 2. 极致缓存友好 (Cache Locality & Direct Execution):
//    不依赖任何 STL 容器或哈希表，通过整型状态变量驱动双指针滑动。
//    指令分支预测准确率高，CPU L1/L2 Cache Prefetcher 可发挥最高效能。
// ==========================================

#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
public:
    int longestOnes(const std::vector<int>& nums, int k) {
        int left = 0;
        int zero_count = 0;
        int max_len = 0;
        const int n = static_cast<int>(nums.size());

        for (int right = 0; right < n; ++right) {
            if (nums[right] == 0) {
                zero_count++;
            }

            while (zero_count > k) {
                if (nums[left] == 0) {
                    zero_count--;
                }
                left++;
            }

            max_len = std::max(max_len, right - left + 1);
        }

        return max_len;
    }
};

// ==========================================
// 本地 Debug 测试入口 (支持自定义交互输入)
// ==========================================
int main() {
    Solution solution;
    int k = 0;
    int n = 0;

    std::cout << "--- LC 1004 最大连续1的个数 III 测试 ---" << std::endl;
    std::cout << "请输入最大可翻转 0 的个数 k: ";
    if (!(std::cin >> k) || k < 0) return 0;

    std::cout << "请输入二进制数组长度 n: ";
    if (!(std::cin >> n) || n <= 0) return 0;

    std::vector<int> nums(n);
    std::cout << "请输入 " << n << " 个数组元素 (仅限 0 或 1，空格分隔): ";
    for (int i = 0; i < n; ++i) {
        std::cin >> nums[i];
    }

    int result = solution.longestOnes(nums, k);

    std::cout << "\n--- 计算结果 ---" << std::endl;
    std::cout << "最长连续 1 的长度: " << result << std::endl;
    std::cout << "----------------------" << std::endl;

    return 0;
}