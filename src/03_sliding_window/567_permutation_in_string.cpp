// LeetCode 567 - Permutation in String
// 难度: Medium
// 提交日期: 2026-08-09
// 解法: 定长滑动窗口 + 栈上 26 频次数组比对
// 时间复杂度: O(N) - N 为 s2 的长度，平移窗口比较频次为 O(1)
// 空间复杂度: O(1) - 仅需 26 长度栈上数组 std::array，Zero Dynamic Allocation
//
// ==========================================
// 核心系统设计与性能思考 (AI Infra 视角):
// ==========================================
// 1. 栈上定长频次表 (Zero-Allocation Vectorization):
//    摒弃 std::unordered_map，使用 std::array<int, 26> 存储频次。
//    数据完全驻留在 CPU 寄存器 / L1 Cache，std::array::operator== 的 26 次 Int 比较
//    会被现代编译器 (GCC/Clang/MSVC) 自动展开 (Loop Unrolling) 甚至使用 SIMD 指令优化。
//
// 2. 定长滑动增量更新 (Incremental State Update):
//    维持窗口大小为 s1.length()，每步仅仅执行 "1 次进窗口 + 1 次出窗口" 的增量修改，
//    状态更新代价极低，严格满足高吞吐实时处理要求。
// ==========================================

#include <iostream>
#include <string>
#include <array>
#include <limits>

class Solution {
public:
    bool checkInclusion(const std::string& s1, const std::string& s2) {
        const int len1 = static_cast<int>(s1.length());
        const int len2 = static_cast<int>(s2.length());

        if (len1 > len2) return false;

        std::array<int, 26> count1{};
        std::array<int, 26> count2{};

        for (int i = 0; i < len1; ++i) {
            count1[s1[i] - 'a']++;
            count2[s2[i] - 'a']++;
        }

        if (count1 == count2) return true;

        for (int right = len1; right < len2; ++right) {
            count2[s2[right] - 'a']++;
            count2[s2[right - len1] - 'a']--;

            if (count1 == count2) return true;
        }

        return false;
    }
};

// ==========================================
// 本地 Debug 测试入口 (支持自定义交互输入)
// ==========================================
int main() {
    Solution solution;
    std::string s1, s2;

    std::cout << "--- LC 567 字符串的排列 测试 ---" << std::endl;
    std::cout << "请输入模式串 s1 (不含空格): ";
    if (!(std::cin >> s1)) return 0;

    std::cout << "请输入主字符串 s2 (不含空格): ";
    if (!(std::cin >> s2)) return 0;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    bool result = solution.checkInclusion(s1, s2);

    std::cout << "\n--- 计算结果 ---" << std::endl;
    std::cout << "s2 是否包含 s1 的排列: " << (result ? "true " : "false ") << std::endl;
    std::cout << "----------------------" << std::endl;

    return 0;
}