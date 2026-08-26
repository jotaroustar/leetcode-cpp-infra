// 文件名: 540_single_element_in_a_sorted_array.cpp
// LeetCode 540 - Single Element in a Sorted Array
// 难度: Medium
// 提交日期: 2026-08-25
// 解法: 奇偶索引对齐二分 (Parity-Aligned Index Binary Search)
// 时间复杂度: O(log N)
// 空间复杂度: O(1)

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

class Solution {
public:
    int singleNonDuplicate(const std::vector<int>& nums) {
        int left = 0;
        int right = static_cast<int>(nums.size()) - 1;

        while (left < right) {
            int mid = left + (right - left) / 2;

            if (mid % 2 == 1) {
                mid--;
            }

            if (nums[mid] == nums[mid + 1]) {
                left = mid + 2;
            }
            else {
                right = mid;
            }
        }

        return nums[left];
    }
};

int main() {
    Solution solution;
    std::string line;

    std::cout << "nums: ";
    if (!std::getline(std::cin, line) || line.empty()) return 0;

    std::stringstream ss(line);
    std::vector<int> nums;
    int val = 0;
    while (ss >> val) {
        nums.push_back(val);
    }

    int result = solution.singleNonDuplicate(nums);

    std::cout << "result: " << result << std::endl;

    return 0;
}