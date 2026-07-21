// LeetCode 011 - Container With Most Water
// 难度: Medium
// 提交日期: 2026-07-21
// 解法: 双指针·短板向内对撞剪枝型 (Two Pointers - Min Height Shrink)
// 时间复杂度: O(n) - 左右指针单向逼近，仅需单次遍历
// 空间复杂度: O(1) - 零堆内存分配 (Zero Allocation)
//
// ==========================================
// 核心系统设计与性能思考 (AI Infra 视角):
// ==========================================
// 1. 物理短板效应与决策单调性剪枝 (Monotonic Search Space Reduction):
//    容积由短板决定：Area = (right - left) * min(height[left], height[right])。
//    若移动长板，底边 (right - left) 必减小，而受限于短板限制，短板不可能变长，Area 必定单调不增。
//    因此移动长板属于无用计算。只有移动短板，才可能遇到更大的高度来弥补底边缩小的损失。
//    单次移动直接剪掉了整整一组以当前短板为端点的无效组合，实现 $O(N^2) -> O(N)$ 的空间物理降维。
//
// 2. CPU 缓存友好与指令流水线无分支化 (Branchless Optimization Awareness):
//    在 C++ 底层，频繁使用 if-else 条件判断会导致分支预测失败（Branch Misprediction）引发 Pipeline Flush。
//    在性能极致场景下，`std::min` 与 `std::max` 可被编译器直接优化为 `cmov` (Conditional Move) 指令，
//    保持连续内存顺序读入时的流水线满载。
//
// ==========================================

#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <string>
#include <limits>

class Solution {
public:
    int maxArea(const std::vector<int>& height) {
        int left = 0;
        int right = static_cast<int>(height.size()) - 1;
        int max_water = 0;

        while (left < right) {
            int current_width = right - left;
            int current_height = std::min(height[left], height[right]);
            int current_water = current_width * current_height;

            max_water = std::max(max_water, current_water);

            if (height[left] < height[right]) {
                ++left;
            }
            else {
                --right;
            }
        }

        return max_water;
    }
};

// ==========================================
// 本地 Debug 测试入口
// ==========================================
int main() {
    Solution solver;

    std::cout << "请输入木板高度数组（空格隔开，按回车结束）: ";
    std::string line;
    std::getline(std::cin, line);

    std::vector<int> height;
    std::stringstream ss(line);
    int h;
    while (ss >> h) {
        height.push_back(h);
    }

    if (height.size() < 2) {
        std::cout << "水槽至少需要 2 根木板！" << std::endl;
        return 0;
    }

    int result = solver.maxArea(height);
    std::cout << "最大盛水量 (Max Water Area): " << result << std::endl;

    return 0;
}