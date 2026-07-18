// LeetCode 001 - Two Sum
// 难度: Easy
// 提交日期: 2026-07-17
// 解法: 哈希表查配对法 (Hash Table - Single Pass)
// 时间复杂度: O(n) - 最坏情况下单次遍历，哈希表平均查找时间为 O(1)
// 空间复杂度: O(n) - 用于存储元素及其索引映射的哈希表开销
//
// ==========================================
// 核心系统设计与性能思考 (AI Infra 视角):
// ==========================================
// 1. 哈希表离散内存与 Cache Miss 风险:
//    std::unordered_map 底层是基于“链地址法”（拉链法）实现的哈希桶结构。
//    相比于 std::vector 的连续物理内存，哈希表的节点在堆上是离散分配的。
//    在处理海量数据时，多级指针跳转会引发高频的 Cache Miss。在 Infra 工程实践中，
//    若对吞吐量有极致要求，通常会选用基于开放寻址法（Open Addressing）的 Flat Hash Map。
//
// 2. 规避动态扩容开销 (Rehash Overhead):
//    std::unordered_map 在元素激增时会触发自动扩容与桶重排（Rehash），产生 O(n) 的瞬时卡顿。
//    在明确数据规模上限的前提下，工程上应优先调用 `num_to_index.reserve(N)` 预分配桶空间，
//    消灭运行时动态分配堆内存与 rehash 的抖动。
//
// 3. 常量引用与零拷贝传递 (Const Reference):
//    参数采用 `const std::vector<int>& nums`。使用 `const` 锁死只读权限，
//    配合引用传递消除整包拷贝，确保在面对超大入参时依然保持原生的物理内存访问效率。
//
// ==========================================
// 关键物理内存指针流转图示 (输入: nums = [2, 7, 11, 15], target = 9):
// ==========================================
// i = 0: nums[0] = 2, complement = 9 - 2 = 7
//        Map 中查找 7 -> 未命中 (End)
//        插入 Map: {2 -> 0}
//
// i = 1: nums[1] = 7, complement = 9 - 7 = 2
//        Map 中查找 2 -> 命中！找到迭代器对应 it->second = 0
//        返回下标组件: {0, 1} -> 算法提前收敛，直接返回结果。
//
// ==========================================

#include <iostream>
#include <vector>
#include <unordered_map>

class Solution {
public:
    std::vector<int> twoSum(const std::vector<int>& nums, int target) {
        // key: 数值, value: 对应的数组下标
        std::unordered_map<int, int> num_to_index;

        // 工程优化提示：如果已知 nums 的尺寸，可以在此处调用 reserve 预控哈希抖动
        // num_to_index.reserve(nums.size());

        for (int i = 0; i < nums.size(); ++i) {
            int complement = target - nums[i];

            // 在哈希表中查找我们需要的那个“另一半”
            auto it = num_to_index.find(complement);
            if (it != num_to_index.end()) {
                // 找到了，返回配对的两个下标（零拷贝构造）
                return { it->second, i };
            }

            // 没找到，把当前的数值和下标存进去
            num_to_index[nums[i]] = i;
        }

        // 若无解则返回空字典（题目边界保证必有唯一解）
        return {};
    }
};

// ==========================================
// 本地 Debug 测试入口 (展示工程完备性)
// ==========================================
int main() {
    Solution solver;

    std::vector<int> nums = { 2, 7, 11, 15 };
    int target = 9;

    std::cout << "Original vector size: " << nums.size() << std::endl;
    std::cout << "Target value sum: " << target << std::endl;

    std::vector<int> result = solver.twoSum(nums, target);

    if (result.size() == 2) {
        std::cout << "Successfully found indices: [" << result[0] << ", " << result[1] << "]" << std::endl;
        std::cout << "Physical memory verification: " << nums[result[0]] << " + " << nums[result[1]] << " == " << target << std::endl;
    }
    else {
        std::cout << "Error: No valid pair found." << std::endl;
    }

    return 0;
}