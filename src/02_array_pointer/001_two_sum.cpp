#include <iostream>
#include <vector>
#include <unordered_map>

/*
====================================================================
LeetCode #001: Two Sum (两数之和)
====================================================================
【题目描述】
给定一个整数数组 nums 和一个整数目标值 target，请你在该数组中找出
和为目标值 target 的那两个整数，并返回它们的数组下标。

【解题思路】
1. 使用哈希表 (std::unordered_map) 来存储 “数值 -> 下标” 的映射。
2. 遍历数组时，对于当前的元素 nums[i]，计算出我们需要的配对数：
   complement = target - nums[i]
3. 在哈希表中查找 complement：
   - 如果找到了，说明之前已经遇到过这个配对数，直接返回其下标和当前下标 {hash_table[complement], i}。
   - 如果没找到，就把当前元素及其下标存入哈希表中，继续向后遍历。
====================================================================
*/

class Solution {
public:
    std::vector<int> twoSum(const std::vector<int>& nums, int target) {
        // key: 数值, value: 对应的数组下标
        std::unordered_map<int, int> num_to_index;

        for (int i = 0; i < nums.size(); ++i) {
            int complement = target - nums[i];

            // 在哈希表中查找我们需要的那个“另一半”
            auto it = num_to_index.find(complement);
            if (it != num_to_index.end()) {
                // 找到了，返回配对的两个下标
                return { it->second, i };
            }

            // 没找到，把当前的数值和下标存进去
            num_to_index[nums[i]] = i;
        }

        // 如果没有解，返回空数组（根据题目保证，本题必定有且仅有一个答案）
        return {};
    }
};

// ====================================================================
// 本地 Debug 测试入口（展示工程完备性）
// ====================================================================
int main() {
    Solution solver;

    // 测试用例 1
    std::vector<int> nums = { 2, 7, 11, 15 };
    int target = 9;

    std::cout << "Test Case: nums = [2, 7, 11, 15], target = 9" << std::endl;

    std::vector<int> result = solver.twoSum(nums, target);

    if (result.size() == 2) {
        std::cout << "Successfully found indices: ["
            << result[0] << ", " << result[1] << "]" << std::endl;
        std::cout << "Values are: " << nums[result[0]]
            << " + " << nums[result[1]] << " = " << target << std::endl;
    }
    else {
        std::cout << "No solution found." << std::endl;
    }

    return 0;
}