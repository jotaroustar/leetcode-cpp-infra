// 文件名: 162_find_peak_element.cpp
// LeetCode 162 - Find Peak Element
// 难度: Medium
// 提交日期: 2026-08-16
// 解法: 梯度爬坡单调收敛 (Gradient Ascent Binary Search)
// 时间复杂度: O(log N)
// 空间复杂度: O(1)

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

class Solution {
public:
    int findPeakElement(const std::vector<int>& nums) {
        int left = 0;
        int right = static_cast<int>(nums.size()) - 1;

        while (left < right) {
            int mid = left + (right - left) / 2;

            if (nums[mid] > nums[mid + 1]) {
                right = mid;
            }
            else {
                left = mid + 1;
            }
        }

        return left;
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

    int result = solution.findPeakElement(nums);

    std::cout << "result: " << result << std::endl;

    return 0;
}