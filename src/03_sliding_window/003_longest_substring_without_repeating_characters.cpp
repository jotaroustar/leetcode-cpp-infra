// LeetCode 003 - Longest Substring Without Repeating Characters
// 难度: Medium
// 提交日期: 2026-08-03
// 解法: 跳跃式滑动窗口 + ASCII 直接映射 (Sliding Window + ASCII Direct Mapping)
// 时间复杂度: O(n) - 右指针遍历一次字符串，左指针实现跳跃式移动
// 空间复杂度: O(1) - 仅需 128 字节栈上固定大小数组
//
// ==========================================
// 核心系统设计与性能思考 (AI Infra 视角):
// ==========================================
// 1. ASCII 直接映射 (Zero Allocation & Cache Locality):
//    对于标准 ASCII 字符集，放弃带来堆内存分配与哈希开销的 std::unordered_map，
//    改用固定大小 std::array<int, 128> 存储字符最近出现的下标，实现严格 O(1) 查找与零动态内存分配。
//
// 2. 双指针跳跃式收缩 (Jump-based Window Shrink):
//    当右指针遇到重复字符时，左指针无需逐步递增，直接利用历史下标跳跃至
//    std::max(left, last_seen[ch] + 1)，彻底避开无效轮询。
// ==========================================

#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <algorithm>

class Solution {
public:
    int lengthOfLongestSubstring(const std::string& s) {
        const int n = static_cast<int>(s.length());
        if (n <= 1) return n;

        std::array<int, 128> last_seen;
        last_seen.fill(-1);

        int max_len = 0;
        int left = 0;

        for (int right = 0; right < n; ++right) {
            const unsigned char ch = static_cast<unsigned char>(s[right]);

            if (ch < 128 && last_seen[ch] >= left) {
                left = last_seen[ch] + 1;
            }

            if (ch < 128) {
                last_seen[ch] = right;
            }
            max_len = std::max(max_len, right - left + 1);
        }

        return max_len;
    }
};

// ==========================================
// 本地 Debug 测试入口
// ==========================================
int main() {
    std::cout << "请输入测试字符串 (例如: abcabcbb): ";
    std::string s;
    if (std::cin >> s) {
        Solution solution;
        int result = solution.lengthOfLongestSubstring(s);

        std::cout << "\n--- 计算结果 ---" << std::endl;
        std::cout << "最长无重复字符子串长度: " << result << std::endl;
        std::cout << "----------------------" << std::endl;
    }
    return 0;
}