// LeetCode 84 - Largest Rectangle in Histogram
// 难度: Hard
// 提交日期: 2026-07-29
// 解法: 单调递增栈 + 首尾双哨兵 (Monotonic Increasing Stack with Double Sentinels)
// 时间复杂度: O(n) - 线性扫描数组，每个元素最多入栈一次、出栈一次，平摊复杂度为常数级
// 空间复杂度: O(n) - 预分配 N + 2 连续空间，零动态扩容开销
//
// ==========================================
// 核心系统设计与性能思考 (AI Infra 视角):
// ==========================================
// 1. 双哨兵无分支设计 (Zero-Branching Sentinel Padding):
//    在原高度数组首尾各压入一个高度为 0 的哨兵节点。
//    - 左哨兵 (0): 保证栈底永远非空，求宽度 (i - st.back() - 1) 时彻底消除了对栈空条件的 if 检查。
//    - 右哨兵 (0): 在遍历末尾触发“断崖”，强行击穿并清空栈内残余元素，避免了主循环后的 Cleanup 拖尾代码。
//
// 2. 内存连续性与 Cache 局部性 (Vector-backed Stack):
//    摒弃 std::stack (底层为 deque 的分块内存分配)，改用 std::vector<int> 模拟栈。
//    配合 reserve(n + 2) 一次性开辟连续内存，极大提升 CPU L1/L2 Cache Line 命中率。
//
// 3. 延迟结算与几何延展 (Geometric Span Evaluation):
//    单调递增栈维护可向右扩展的柱体索引。遇到矮柱子时确定栈顶柱子的右边界，
//    弹栈后的新栈顶即为左边界，以 O(1) 平摊时间完成最大矩形面积计算。
// ==========================================

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

class Solution {
public:
    int largestRectangleArea(std::vector<int>& heights) {
        const size_t n = heights.size();
        if (n == 0) return 0;

        std::vector<int> padded_heights;
        padded_heights.reserve(n + 2);
        padded_heights.push_back(0); 
        padded_heights.insert(padded_heights.end(), heights.begin(), heights.end());
        padded_heights.push_back(0); 

        std::vector<int> st;
        st.reserve(n + 2);

        int max_area = 0;
        const int total_len = static_cast<int>(padded_heights.size());

        for (int i = 0; i < total_len; ++i) {
            while (!st.empty() && padded_heights[i] < padded_heights[st.back()]) {
                int mid_idx = st.back();
                st.pop_back();

                int height = padded_heights[mid_idx];
                int width = i - st.back() - 1; 

                max_area = std::max(max_area, height * width);
            }
            st.push_back(i);
        }

        return max_area;
    }
};

// ==========================================
// 本地 Debug 测试入口 (终端交互)
// ==========================================
int main() {
    std::cout << "请输入柱状图高度序列（空格隔离，按回车结束）: ";
    std::string line;
    std::getline(std::cin, line);

    std::stringstream ss(line);
    std::vector<int> heights;
    int h;
    while (ss >> h) {
        heights.push_back(h);
    }

    if (heights.empty()) {
        std::cout << "未输入任何有效高度数据。" << std::endl;
        return 0;
    }

    Solution solution;
    int max_area = solution.largestRectangleArea(heights);

    std::cout << "\n--- 计算结果 (柱状图最大矩形面积) ---" << std::endl;
    std::cout << "输入高度: [ ";
    for (int h_val : heights) {
        std::cout << h_val << " ";
    }
    std::cout << "]" << std::endl;

    std::cout << "最大面积: " << max_area << std::endl;
    std::cout << "------------------------------------------" << std::endl;

    return 0;
}