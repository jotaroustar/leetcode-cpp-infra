// LeetCode 424 - Longest Repeating Character Replacement
// 难度: Medium
// 提交日期: 2026-08-08
// 解法: 滑动窗口 + 历史最高频次单调不降优化
// 时间复杂度: O(N) - 字符串仅单次平移遍历
// 空间复杂度: O(1) - 仅需 26 长度栈上数组 std::array，Zero Dynamic Allocation
//
// ==========================================
// 核心系统设计与性能思考 (AI Infra 视角):
// ==========================================
// 1. 历史最大频次单调性 (Monotonic Max Frequency):
//    求解目标为"最大窗口长度"，因此仅需在出现更长窗口时更新 max_count。
//    当窗口收缩时放弃下调 max_count，避免了无意义的 O(26) 重新扫描频次表，
//    将每次滑动的时间开销极致压缩至 O(1)。
//
// 2. 连续内存与零分配 (Zero Allocation):
//    直接使用栈分配 std::array<int, 26>，无堆内存分配与垃圾回收开销，
//    完全驻留 CPU L1 Cache，极大提升 CPU 指令级并行（ILP）效率。
// ==========================================

#include <iostream>
#include <string>
#include <array>
#include <algorithm>
#include <limits>

class Solution {
public:
    int characterReplacement(const std::string& s, int k) {
        std::array<int, 26> counts{};
        int left = 0;
        int max_count = 0;
        const int n = static_cast<int>(s.length());

        for (int right = 0; right < n; ++right) {
            const int current_char = s[right] - 'A';
            counts[current_char]++;
            max_count = std::max(max_count, counts[current_char]);
            if (right - left + 1 - max_count > k) {
                counts[s[left] - 'A']--;
                left++;
            }
        }
        return n - left;
    }
};

// ==========================================
// 本地 Debug 测试入口 (增强容错版)
// ==========================================
int main() {
    Solution solution;
    std::string s;
    int k = 0;

    std::cout << "--- LC 424 替换后的最长重复字符 测试 ---" << std::endl;
    std::cout << "请输入仅包含大写英文字母的字符串 s: ";
    if (!(std::cin >> s)) return 0;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "请输入最大可替换字符数 k: ";
    if (!(std::cin >> k) || k < 0) return 0;

    int result = solution.characterReplacement(s, k);

    std::cout << "\n--- 计算结果 ---" << std::endl;
    std::cout << "最长重复字符子串长度: " << result << std::endl;
    std::cout << "----------------------" << std::endl;

    return 0;
}