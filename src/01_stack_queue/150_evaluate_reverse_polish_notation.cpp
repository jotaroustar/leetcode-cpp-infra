// LeetCode 150 - Evaluate Reverse Polish Notation
// 难度: Medium
// 提交日期: 2026-08-02
// 解法: 栈操作引擎 + 分支优化 (Stack-Based Evaluation Engine)
// 时间复杂度: O(n) - 线性扫描表达式 Token 序列，每个 Token 入栈/出栈一次
// 空间复杂度: O(n) - 栈空间最大占用 N/2 个操作数，预分配连续内存
//
// ==========================================
// 核心系统设计与性能思考 (AI Infra 视角):
// ==========================================
// 1. 栈虚拟机求值范式 (Stack-Based Engine):
//    逆波兰表达式天然契合 Stack Architecture。消除前缀/中缀表达式的优先级括号解析，
//    利用显式操作数栈实现单次扫描 O(1) 平摊状态转移。
//
// 2. 防溢出与 Zero-Reallocation:
//    使用 std::vector<long long> 存储中间结果，防止乘法等运算在 int32 下溢出。
//    调用 reserve(tokens.size()) 一次性开辟连续内存，极大降低内存碎片并提升 Cache Line 命中率。
//
// 3. 极速运算符派发 (Branch-Friendly Dispatch):
//    判断运算符时先比对字符串长度（只有 1 位且为运算符才派发），利用 switch-case 触发
//    编译器跳转表（Jump Table）优化，比连续 string == 比对性能提升显著。
// ==========================================

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>

class Solution {
public:
    int evalRPN(const std::vector<std::string>& tokens) {
        const size_t n = tokens.size();
        if (n == 0) return 0;

        std::vector<long long> st;
        st.reserve(n);

        for (const std::string& token : tokens) {
            if (token.size() == 1 && (token[0] == '+' || token[0] == '-' || token[0] == '*' || token[0] == '/')) {
                long long op2 = st.back(); st.pop_back();
                long long op1 = st.back(); st.pop_back(); 
                switch (token[0]) {
                case '+': st.push_back(op1 + op2); break;
                case '-': st.push_back(op1 - op2); break;
                case '*': st.push_back(op1 * op2); break;
                case '/': st.push_back(op1 / op2); break; 
                }
            }
            else {
                st.push_back(std::stoll(token));
            }
        }

        return static_cast<int>(st.back());
    }
};

// ==========================================
// 本地 Debug 测试入口 (终端交互)
// ==========================================
int main() {
    std::cout << "请输入逆波兰表达式 Token 序列: ";
    std::string line;
    std::getline(std::cin, line);

    std::stringstream ss(line);
    std::vector<std::string> tokens;
    std::string token;

    while (ss >> token) {
        tokens.push_back(token);
    }

    if (tokens.empty()) {
        std::cout << "未输入任何有效 Token。" << std::endl;
        return 0;
    }

    Solution solution;
    try {
        int result = solution.evalRPN(tokens);

        std::cout << "\n--- 计算结果 (逆波兰表达式求值) ---" << std::endl;
        std::cout << "Token 序列: [ ";
        for (const auto& t : tokens) {
            std::cout << t << " ";
        }
        std::cout << "]" << std::endl;

        std::cout << "求值结果  : " << result << std::endl;
        std::cout << "------------------------------------------" << std::endl;
    }
    catch (const std::exception&) {
        std::cout << "表达式解析错误，请检查输入格式。" << std::endl;
    }

    return 0;
}