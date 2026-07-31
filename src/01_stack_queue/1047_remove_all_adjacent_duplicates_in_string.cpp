// LeetCode 1047 - Remove All Adjacent Duplicates In String
// 难度: Easy
// 提交日期: 2026-07-31
// 解法: 隐式字符串栈 (In-Place String Stack Engine)
// 时间复杂度: O(n) - 线性扫描字符串，每个字符最多入栈出栈一次
// 空间复杂度: O(1) - 辅助空间除了返回值外无需额外分配，预分配 O(n) 连续内存
//
// ==========================================
// 核心系统设计与性能思考 (AI Infra 视角):
// ==========================================
// 1. 隐式栈设计 (In-Place String as Stack):
//    摒弃 std::stack<char>（底层为 deque 分块内存），直接利用 std::string 本身作为栈。
//    通过 push_back() 和 pop_back() 实现 O(1) 栈操作，避免二次拼装字符串的开销。
//
// 2. 内存预分配 (Zero-Allocation Optimization):
//    在处理前调用 stk.reserve(s.size()) 一次性分配最大可能内存，
//    完全杜绝字符串动态增长过程中的 realloc 与内存拷贝，对 CPU Cache Line 极其友好。
// ==========================================

#include <iostream>
#include <string>
#include <algorithm>

class Solution {
public:
    std::string removeDuplicates(const std::string& s) {
        std::string stk;
        stk.reserve(s.size());

        for (char ch : s) {
            if (!stk.empty() && stk.back() == ch) {
                stk.pop_back(); 
            }
            else {
                stk.push_back(ch); 
            }
        }

        return stk;
    }
};

// ==========================================
// 本地 Debug 测试入口 (终端交互)
// ==========================================
int main() {
    std::cout << "请输入测试字符串 (例如: abbaca): ";
    std::string input;
    if (!(std::cin >> input)) {
        std::cout << "未输入有效字符串。" << std::endl;
        return 0;
    }

    Solution solution;
    std::string result = solution.removeDuplicates(input);

    std::cout << "\n--- 计算结果 (删除相邻重复项) ---" << std::endl;
    std::cout << "输入字符串: " << input << std::endl;
    std::cout << "消除后结果: " << result << std::endl;
    std::cout << "------------------------------------------" << std::endl;

    return 0;
}