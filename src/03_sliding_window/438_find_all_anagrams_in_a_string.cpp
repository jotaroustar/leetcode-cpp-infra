// LeetCode 438 - Find All Anagrams in a String
// 难度: Medium
// 提交日期: 2026-08-05
// 解法: 定长滑动窗口 + 栈上固定频次表比对
// 时间复杂度: O(N) - N 为字符串 s 的长度，每次滑动比较 26 个字母频次为 O(1)
// 空间复杂度: O(1) - 仅占用 26 长度的 std::array，Zero Dynamic Allocation
//
// ==========================================
// 核心系统设计与性能思考 (AI Infra 视角):
// ==========================================
// 1. 栈上定长频次表 (Zero-Allocation Vectorization):
//    摒弃 std::unordered_map，使用 std::array<int, 26> 存储频次。
//    数据完全驻留在 CPU 寄存器 / L1 Cache，std::array::operator== 的 26 次 Int 比较
//    会被现代编译器 (GCC/Clang) 自动展开 (Loop Unrolling) 甚至使用 AVX2/NEON 指令优化。
//
// 2. 定长滑动增量更新 (Incremental State Update):
//    维持窗口大小为 p.length()，每步仅仅执行 "1 次进窗口 + 1 次出窗口" 的增量修改，
//    状态更新代价极低，严格满足高吞吐实时处理要求。
// ==========================================

#include <iostream>
#include <vector>
#include <string>
#include <array>

class Solution {
public:
    std::vector<int> findAnagrams(const std::string& s, const std::string& p) {
        std::vector<int> result;
        const int s_len = static_cast<int>(s.length());
        const int p_len = static_cast<int>(p.length());

        if (s_len < p_len) return result;

        std::array<int, 26> p_count{};
        std::array<int, 26> window_count{};

        for (int i = 0; i < p_len; ++i) {
            p_count[p[i] - 'a']++;
            window_count[s[i] - 'a']++;
        }

        if (p_count == window_count) {
            result.push_back(0);
        }

        for (int right = p_len; right < s_len; ++right) {
            window_count[s[right] - 'a']++;
            window_count[s[right - p_len] - 'a']--;

            if (p_count == window_count) {
                result.push_back(right - p_len + 1);
            }
        }

        return result;
    }
};

// ==========================================
// 本地 Debug 测试入口 (支持自定义交互输入)
// ==========================================
int main() {
    Solution solution;
    std::string s, p;

    std::cout << "--- LC 438 找到字符串中所有字母异位词 测试 ---" << std::endl;
    std::cout << "请输入主字符串 s: ";
    if (!(std::cin >> s)) return 0;

    std::cout << "请输入模式串 p: ";
    if (!(std::cin >> p)) return 0;

    std::vector<int> result = solution.findAnagrams(s, p);

    std::cout << "\n--- 计算结果 ---" << std::endl;
    std::cout << "异位词起始索引列表: [";
    for (size_t i = 0; i < result.size(); ++i) {
        std::cout << result[i] << (i + 1 < result.size() ? ", " : "");
    }
    std::cout << "]" << std::endl;
    std::cout << "----------------------" << std::endl;

    return 0;
}