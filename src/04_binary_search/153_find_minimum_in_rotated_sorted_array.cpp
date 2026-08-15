// 文件名: 153_find_minimum_in_rotated_sorted_array.cpp
// LeetCode 153 - Find Minimum in Rotated Sorted Array
// 难度: Medium
// 提交日期: 2026-08-15
// 解法: 右端点基准单调性收敛 (Right-Bound Pivot Convergence)
// 时间复杂度: O(log N)
// 空间复杂度: O(1)

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

class Solution {
public:
    int findMin(const std::vector<int>& nums) {
        int left = 0;
        int right = static_cast<int>(nums.size()) - 1;

        while (left < right) {
            int mid = left + (right - left) / 2;

            if (nums[mid] < nums[right]) {
                right = mid;
            }
            else {
                left = mid + 1;
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

    int result = solution.findMin(nums);

    std::cout << "result: " << result << std::endl;

    return 0;
}