// LeetCode 904 - Fruit Into Baskets
// 难度: Medium
// 提交日期: 2026-08-07
// 解法: 变长滑动窗口 + 种类字典映射（At Most 2 Distinct Types）
// 时间复杂度: O(N) - 左右指针各遍历一次数组，哈希表操作均为 O(1)
// 空间复杂度: O(1) - 哈希表大小上限为 3，内存占用恒定
//
// ==========================================
// 核心系统设计与性能思考 (AI Infra 视角):
// ==========================================
// 1. "至多 K 种元素"滑动窗口模型 (At Most K Distinct Elements Model):
//    将业务场景抽象为求解包含至多 2 种不同元素的最长连续子数组。
//    利用 std::unordered_map 维护当前窗口内的水果类型与出现频次。
//
// 2. 状态映射空间上限约束 (Bounded Hash Map Footprint):
//    由于控制逻辑保证篮子内种类一到 3 种就立刻收缩，哈希表最多仅驻留 3 个节点。
//    不存在 Rehash 和频繁 Dynamic Allocation，性能极佳。
// ==========================================

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <limits>

class Solution {
public:
    int totalFruit(const std::vector<int>& fruits) {
        std::unordered_map<int, int> basket;
        int left = 0;
        int max_picked = 0;
        const int n = static_cast<int>(fruits.size());

        for (int right = 0; right < n; ++right) {
            basket[fruits[right]]++;

            while (basket.size() > 2) {
                int left_fruit = fruits[left];
                basket[left_fruit]--;
                if (basket[left_fruit] == 0) {
                    basket.erase(left_fruit);
                }
                left++;
            }

            max_picked = std::max(max_picked, right - left + 1);
        }

        return max_picked;
    }
};

// ==========================================
// 本地 Debug 测试入口 (支持自定义交互输入)
// ==========================================
int main() {
    Solution solution;
    int n = 0;

    std::cout << "--- LC 904 水果成篮 测试 ---" << std::endl;
    std::cout << "请输入水果树数组长度 n: ";
    if (!(std::cin >> n) || n <= 0) return 0;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::vector<int> fruits(n);
    std::cout << "请输入 " << n << " 个水果种类编号 (空格分隔): ";
    for (int i = 0; i < n; ++i) {
        std::cin >> fruits[i];
    }

    int result = solution.totalFruit(fruits);

    std::cout << "\n--- 计算结果 ---" << std::endl;
    std::cout << "最多可采摘的水果总量: " << result << std::endl;
    std::cout << "----------------------" << std::endl;

    return 0;
}