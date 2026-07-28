// LeetCode 503 - Next Greater Element II
// 难度: Medium
// 提交日期: 2026-07-28
// 解法: 单调递减栈 + 虚拟双倍数组 (Monotonic Decreasing Stack + Virtual Double-Length Array)
// 时间复杂度: O(n) - 循环走 2n 次，每个下标最多入栈一次、出栈一次，平摊复杂度为 O(1)
// 空间复杂度: O(n) - 单调栈最多同时保存 n 个元素的索引
//
// ==========================================
// 核心系统设计与性能思考 (AI Infra 视角):
// ==========================================
// 1. 环形数组的虚拟展开与控制流打断 (Virtual Array Expansion & Gatekeeping):
//    通过 modulo 运算 (`i % n`) 将环形逻辑平铺为 $2N$ 次虚拟遍历。
//    关键优化点在于第二轮（$i \ge n$）利用 `if (i < n)` 强行拦截入栈操作：只利用第二轮元素去“解封/结算”第一轮遗留在栈中的残余索引，
//    避免了重复索引入栈引发的无限循环与不必要的内存增长。
//
// 2. 内存连续性与 Cache 友好度 (Memory Locality & Index Storing):
//    栈内仅存储原生 `int` 索引而非复杂结构体或元素值。
//    索引连续寻址天然契合硬件 Cache Line 布局，消除了指针追溯（Pointer Chasing）带来的 L1/L2 Cache Miss 开销。
//
// 3. 结果向量预分配与缺省状态填充 (Pre-allocation & Zero-overhead Defaults):
//    结果向量 `answer` 初始化时直接预分配空间并缺省填充 `-1`。
//    在遇到更大元素时才进行“延迟更新”；遍历结束后，未能被击穿的全局最大值天然保留 `-1`，消除了额外的逻辑特判与二次扫描。
// ==========================================

#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <sstream>

class Solution {
public:
    std::vector<int> nextGreaterElements(const std::vector<int>& nums) {
        const size_t n = nums.size();
        std::vector<int> answer(n, -1);
        std::stack<int> st;

        const int total_iterations = static_cast<int>(2 * n);
        for (int i = 0; i < total_iterations; ++i) {
            const int idx = i % static_cast<int>(n);

            while (!st.empty() && nums[idx] > nums[st.top()]) {
                answer[st.top()] = nums[idx];
                st.pop();
            }

            if (i < static_cast<int>(n)) {
                st.push(idx);
            }
        }

        return answer;
    }
};

// ==========================================
// 本地 Debug 测试入口
// ==========================================
int main() {
    std::cout << "请输入环形数组序列（空格隔离，按回车结束）: ";
    std::string line;
    std::getline(std::cin, line);

    std::stringstream ss(line);
    std::vector<int> nums;
    int val;
    while (ss >> val) {
        nums.push_back(val);
    }

    if (nums.empty()) {
        std::cout << "未输入任何有效数据。" << std::endl;
        return 0;
    }

    Solution solution;
    std::vector<int> result = solution.nextGreaterElements(nums);

    std::cout << "\n--- 计算结果 (下一个更大元素) ---" << std::endl;
    std::cout << "输入数组: [ ";
    for (int x : nums) {
        std::cout << x << " ";
    }
    std::cout << "]" << std::endl;

    std::cout << "计算结果: [ ";
    for (int x : result) {
        std::cout << x << " ";
    }
    std::cout << "]" << std::endl;
    std::cout << "------------------------------------------" << std::endl;

    return 0;
}