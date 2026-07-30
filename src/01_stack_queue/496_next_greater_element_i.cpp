// LeetCode 496 - Next Greater Element I
// 难度: Easy
// 提交日期: 2026-07-30
// 解法: 单调递减栈 + 哈希表预处理 (Monotonic Stack + Hash Map Preprocessing)
// 时间复杂度: O(n + m) - n 为 nums2 长度，m 为 nums1 长度。nums2 每个元素进出栈一次，nums1 查表开销 O(1)
// 空间复杂度: O(n) - 哈希表与单调栈均预分配空间，最大占用 O(n) 内存
//
// ==========================================
// 核心系统设计与性能思考 (AI Infra 视角):
// ==========================================
// 1. 反客为主与状态预处理 (Precomputed Mapping):
//    因为 nums1 是 nums2 的子集，直接在 nums2 上构建单调递减栈。
//    一旦触发弹栈，当前元素即为出栈元素的“下一个更大值”，即时写入哈希表。
//
// 2. 哈希桶预分配 (Hash Bucket Pre-allocation):
//    使用 std::unordered_map<int, int> 记录映射。在写入前显式调用 reserve(n)，
//    彻底消除哈希表在动态插入过程中的 Rehash（重哈希）开销。
//
// 3. 连续内存栈 (Vector-backed Stack):
//    使用 std::vector<int> 模拟单调栈，通过 reserve(n) 一次性预分配连续内存，
//    确保入栈出栈操作对 CPU L1/L2 Cache Line 极其友好。
// ==========================================

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>

class Solution {
public:
    std::vector<int> nextGreaterElement(const std::vector<int>& nums1, const std::vector<int>& nums2) {
        const size_t n2 = nums2.size();
        const size_t n1 = nums1.size();
        if (n1 == 0 || n2 == 0) return {};

        std::unordered_map<int, int> next_greater_map;
        next_greater_map.reserve(n2);

        std::vector<int> st;
        st.reserve(n2);

        for (int num : nums2) {
            while (!st.empty() && num > st.back()) {
                next_greater_map[st.back()] = num;
                st.pop_back();
            }
            st.push_back(num);
        }

        std::vector<int> ans(n1, -1);
        for (size_t i = 0; i < n1; ++i) {
            auto it = next_greater_map.find(nums1[i]);
            if (it != next_greater_map.end()) {
                ans[i] = it->second;
            }
        }

        return ans;
    }
};

// ==========================================
// 本地 Debug 测试入口 (终端交互)
// ==========================================
int main() {
    std::string line1, line2;
    std::cout << "请输入 nums1 (子集数组，空格隔离，按回车结束): ";
    std::getline(std::cin, line1);

    std::cout << "请输入 nums2 (目标数组，空格隔离，按回车结束): ";
    std::getline(std::cin, line2);

    std::stringstream ss1(line1), ss2(line2);
    std::vector<int> nums1, nums2;
    int val;

    while (ss1 >> val) nums1.push_back(val);
    while (ss2 >> val) nums2.push_back(val);

    if (nums1.empty() || nums2.empty()) {
        std::cout << "输入数组不能为空。" << std::endl;
        return 0;
    }

    Solution solution;
    std::vector<int> result = solution.nextGreaterElement(nums1, nums2);

    std::cout << "\n--- 计算结果 (下一个更大元素 I) ---" << std::endl;
    std::cout << "nums1 : [ ";
    for (int x : nums1) std::cout << x << " ";
    std::cout << "]\nnums2 : [ ";
    for (int x : nums2) std::cout << x << " ";
    std::cout << "]\n结果  : [ ";
    for (int x : result) std::cout << x << " ";
    std::cout << "]" << std::endl;
    std::cout << "------------------------------------------" << std::endl;

    return 0;
}