// LeetCode 225 - Implement Stack using Queues
// 难度: Easy
// 提交日期: 2026-07-25
// 解法: 单队列环形旋转 (Single Queue Rotate Approach)
// 时间复杂度: push 为 O(n)，pop / top / empty 为 O(1)
// 空间复杂度: O(n) - 依靠单一 std::queue 保存栈内数据
//
// ==========================================
// 核心系统设计与性能思考 (AI Infra 视角):
// ==========================================
// 1. 单队列环形旋转 (Single-Queue Ring Rotation) 与不变式维护 (Invariant Preservation):
//    无需引入辅助队列，利用队列 FIFO 的拓扑特性，在 `push` 时执行 $N$ 次入队-出队操作（`rotate`），
//    使新元素直接旋转至队头。时刻保持 `q.front()` 指向栈顶的不变式，将弹栈与查看栈顶的开销降至 O(1)。
//
// 2. CPU Cache 友好性与内存局部性 (Cache Line & Locality Optimization):
//    相较于双队列在两个容器之间频繁分配指针与内存搬运，单队列方案避免了内存碎片，
//    显著提高了 CPU L1/L2 Cache 命中率。在现代微架构下，单队列的连续内存操作效率远高于多容器交替搬运。
//
// 3. Modern C++ 接口规范与 const 正确性 (Const-Correctness):
//    `top()` 和 `empty()` 被严格标记为 `const` 成员函数，确保只读语义；
//    显式声明 `MyStack() = default;`，遵循 C++11 现代标准，避免未定义的隐式构造逻辑。
// ==========================================

#include <iostream>
#include <queue>
#include <string>
#include <sstream>
#include <iomanip>

class MyStack {
private:
    std::queue<int> q;

public:
    MyStack() = default;

    void push(int x) {
        int n = q.size();
        q.push(x);

        for (int i = 0; i < n; ++i) {
            q.push(q.front());
            q.pop();
        }
    }

    int pop() {
        int val = q.front();
        q.pop();
        return val;
    }

    int top() const {
        return q.front();
    }

    bool empty() const {
        return q.empty();
    }
};

// ==========================================
// 本地 Debug 测试入口 (Drain Test)
// ==========================================
int main() {
    MyStack myStack;

    std::cout << "请输入压栈元素（空格隔离，按回车结束）: ";
    std::string line;
    std::getline(std::cin, line);

    std::stringstream ss(line);
    int num;
    while (ss >> num) {
        myStack.push(num);
    }

    if (myStack.empty()) {
        std::cout << "未输入任何元素。" << std::endl;
        return 0;
    }

    std::cout << "\n--- 开始连续出栈测试 (Drain Test) ---" << std::endl;

    while (!myStack.empty()) {
        std::cout << "当前栈顶 (top): " << std::setw(4) << myStack.top();
        int popped = myStack.pop();
        std::cout << " | 执行出栈 (pop): " << std::setw(4) << popped << std::endl;
    }

    std::cout << "------------------------------------------" << std::endl;
    std::cout << "测试完成！当前栈 empty() 状态: "
        << (myStack.empty() ? "true (已清空)" : "false (异常)") << std::endl;

    return 0;
}