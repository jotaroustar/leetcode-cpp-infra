// LeetCode 020 - Valid Parentheses
// 难度: Easy
// 提交日期: 2026-07-23
// 解法: 栈匹配与对称性约束 (LIFO Stack Matching)
// 时间复杂度: O(n) - 单次线性扫描，每个字符入栈出栈至多一次
// 空间复杂度: O(n) - 最坏情况下（全为左括号）需压入 n 个字符
//
// ==========================================
// 核心系统设计与性能思考 (AI Infra 视角):
// ==========================================
// 1. LIFO 特性与函数调用栈 (Call Stack) 的物理映射:
//    括号匹配本质上是“最后未闭合的左括号必须最先被匹配”，这与 CPU 的函数调用栈 (Call Stack)
//    以及递归恢复现场的内存行为完全一致。`std::stack` 提供了最自然的数据结构抽象。
//
// 2. 内存连续性与 STL 容器选择 (std::deque vs std::vector):
//    `std::stack` 的默认底层容器是 `std::deque`（分段连续内存）。在频繁 Push/Pop 时，
//    若对内存分配（Allocation Overhead）和 CPU Cache 命中率有极高要求，
//    工业界常采用 `std::vector` 或直接用 `std::string` 来模拟栈（物理连续内存，极致利用 L1/L2 Cache）。
//
// 3. 奇数长度剪枝与栈空防御 (Defensive Guard Conditions):
//    - 奇数长度直接剪枝 ($O(1)$ 判定)，避免无效遍历。
//    - 遇到右括号时必须先检查 `st.empty()`，防止对空栈调用 `top()` 导致段错误 (Segmentation Fault)。
//
// ==========================================

#include <iostream>
#include <string>
#include <stack>
#include <unordered_map>
#include <sstream>

class Solution {
public:
    bool isValid(const std::string& s) {
        if (s.length() % 2 != 0) {
            return false;
        }

        std::unordered_map<char, char> pairs = {
            {')', '('},
            {']', '['},
            {'}', '{'}
        };

        std::stack<char> st;

        for (char ch : s) {
            if (pairs.count(ch)) {
                if (st.empty() || st.top() != pairs[ch]) {
                    return false;
                }
                st.pop();
            }
            else {
                st.push(ch);
            }
        }


        return st.empty();
    }
};

// ==========================================
// 本地 Debug 测试入口
// ==========================================
int main() {
    Solution solver;

    std::cout << "===== LeetCode 020 Valid Parentheses 本地测试 =====\n";
    std::cout << "请输入待测试的括号字符串（例如 ()[]{} 或 ([)] ）: ";

    std::string input;
    if (std::cin >> input) {
        std::cout << std::boolalpha; 
        bool result = solver.isValid(input);

        std::cout << "输入字符串: \"" << input << "\"\n";
        std::cout << "匹配结果 (Is Valid): " << result << std::endl;
    }

    return 0;
}