// LeetCode 739 - Daily Temperatures
// 难度: Medium
// 提交日期: 2026-07-27
// 解法: 单调递减栈 (Monotonic Decreasing Stack)
// 时间复杂度: O(n) - 线性扫描数组，每个元素最多入栈一次、出栈一次，平摊复杂度为常数级
// 空间复杂度: O(n) - 最坏情况下（如严格单调递减序列），单调栈需占用 O(n) 的内存空间
//
// ==========================================
// 核心系统设计与性能思考 (AI Infra 视角):
// ==========================================
// 1. 单调栈的状态维护与平摊分析 (Amortized Analysis):
//    我们需要寻找右侧首个大于当前元素的“未来目标”。顺序遍历数组时，维护一个存储索引的单调递减栈。
//    当遇到温度高于栈顶对应温度时，触发“延迟计算”：连续弹出栈顶并更新对应索引的等待天数差值。
//    每个索引经历 1 次 Push 和 1 次 Pop，总开销严格锁定为 $O(N)$，消除暴力解法的 $O(N^2)$ 遍历。
//
// 2. 内存连续性与 Cache 友好度 (Memory Locality & Index Storing):
//    栈内仅存储原始数组的 `int` 索引，而非封装的结构体或对象指针。
//    索引寻址天然契合连续内存布局，极大地提高了 CPU L1/L2 Cache Line 的利用率，降低随机内存访问延迟。
//
// 3. 内存预分配策略 (Pre-allocation):
//    结果向量 `answer` 在初始化阶段直接按数组尺寸预分配并缺省填充 0。
//    这避免了运行期 `push_back` 触发的向量频繁 Reallocation 及内存拷贝开销，同时也自动处理了“后续无更高温度”的边界情况。
// ==========================================

#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <sstream>

class Solution {
public:
    std::vector<int> dailyTemperatures(const std::vector<int>& temperatures) {
        const size_t n = temperatures.size();
        std::vector<int> answer(n, 0); 
        std::stack<int> st;           

        for (int i = 0; i < static_cast<int>(n); ++i) {
            while (!st.empty() && temperatures[i] > temperatures[st.top()]) {
                int prevIdx = st.top();
                st.pop();
                answer[prevIdx] = i - prevIdx;
            }
            st.push(i);
        }

        return answer;
    }
};

// ==========================================
// 本地 Debug 测试入口
// ==========================================
int main() {
    std::cout << "请输入每日温度序列（空格隔离，按回车结束）: ";
    std::string line;
    std::getline(std::cin, line);

    std::stringstream ss(line);
    std::vector<int> temperatures;
    int temp;
    while (ss >> temp) {
        temperatures.push_back(temp);
    }

    if (temperatures.empty()) {
        std::cout << "未输入任何有效温度数据。" << std::endl;
        return 0;
    }

    Solution solution;
    std::vector<int> result = solution.dailyTemperatures(temperatures);

    std::cout << "\n--- 计算结果 (每日需等待的天数) ---" << std::endl;
    std::cout << "输入温度: [ ";
    for (int t : temperatures) {
        std::cout << t << " ";
    }
    std::cout << "]" << std::endl;

    std::cout << "等待天数: [ ";
    for (int days : result) {
        std::cout << days << " ";
    }
    std::cout << "]" << std::endl;
    std::cout << "------------------------------------------" << std::endl;

    return 0;
}