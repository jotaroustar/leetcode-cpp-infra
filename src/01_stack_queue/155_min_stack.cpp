// LeetCode 155 - Min Stack
// 难度: Medium
// 提交日期: 2026-07-23
// 解法: 状态增强单栈 (Single Stack with State Augmentation)
// 时间复杂度: O(1) - push, pop, top, getMin 所有均在常数时间内完成
// 空间复杂度: O(n) - 依靠 vector 保存数值与当前历史最小值快照的二元组
//
// ==========================================
// 核心系统设计与性能思考 (AI Infra 视角):
// ==========================================
// 1. 状态增强 (State Augmentation) 与无开销状态回滚:
//    相比传统的双栈（一个数据栈 + 一个辅助最小值栈）方案，采用 `std::pair<int, int>` 
//    将“值”与“入栈时刻的历史最小值”强绑定封装。当发生 `pop()` 操作时，
//    下层的最小值状态随栈顶指针自然倒退，无需任何分支判断或二次弹出逻辑。
//
// 2. 连续内存与 CPU Cache 亲和性 (Cache Affinity):
//    底层选用 `std::vector` 作为容器，元素在内存中物理连续。相比 `std::list`（节点指针分散）
//    或 `std::deque`（分段缓冲区），连续内存能极大提升 L1/L2 Cache 命中率，
//    并触发 CPU 硬件预取器 (Hardware Prefetcher) 的预取优化。
//
// 3. I/O 流解绑与 Benchmarking 延迟消除:
//    在构造函数中引入 `std::ios::sync_with_stdio(false)`，切断 C++ 流与 C 风格 I/O 缓冲区的同步，
//    避免在平台测试（如 LeetCode）的大量测试用例运行中产生额外的 I/O 阻塞。
// ==========================================

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <string>
#include <sstream>

class MinStack {
private:
    std::vector<std::pair<int, int>> st;

public:
    MinStack() {
        // 解除 C/C++ 流同步，优化本地/测试平台性能
        std::ios::sync_with_stdio(false);
        std::cin.tie(nullptr);
    }

    void push(int value) {
        if (st.empty()) {
            st.push_back({ value, value });
        }
        else {
            st.push_back({ value, std::min(value, st.back().second) });
        }
    }

    void pop() {
        st.pop_back();
    }

    int top() {
        return st.back().first;
    }

    int getMin() {
        return st.back().second;
    }
    /*bool empty() const {
        return st.empty();
    }*/
};

// ==========================================
// 本地 Debug 测试入口
// ==========================================
int main() {
    MinStack minStack;

    std::cout << "请输入压栈元素（空格隔离，按回车结束）: ";
    std::string line;
    std::getline(std::cin, line);

    std::stringstream ss(line);
    int num;
    while (ss >> num) {
        minStack.push(num);
    }

    std::cout << "输出当前最小值: " << minStack.getMin() << std::endl;

    minStack.pop();
    std::cout << "已执行出栈操作。" << std::endl;

    std::cout << "输出当前栈顶: " << minStack.top() << std::endl;
    std::cout << "输出当前最小值: " << minStack.getMin() << std::endl;

    /*minStack.pop();
    std::cout << "已执行 1 次出栈操作。" << std::endl;

    if (!minStack.empty()) {
        std::cout << "输出当前栈顶: " << minStack.top() << std::endl;
        std::cout << "输出当前最小值: " << minStack.getMin() << std::endl;
    }
    else {
        std::cout << "提示: 执行出栈后，栈已清空（无法继续读取栈顶与最小值）。" << std::endl;
    }*/

    return 0;
}