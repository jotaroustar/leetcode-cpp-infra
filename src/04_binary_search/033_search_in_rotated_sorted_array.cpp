// 文件名: 033_search_in_rotated_sorted_array.cpp
// LeetCode 033 - Search in Rotated Sorted Array
// 难度: Medium
// 提交日期: 2026-08-14
// 解法: 局部有序二分查找 (Interval Monotonicity Discrimination)
// 时间复杂度: O(log N)
// 空间复杂度: O(1)

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

class Solution {
public:
    int search(const std::vector<int>& nums, int target) {
        int left = 0;
        int right = static_cast<int>(nums.size()) - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (nums[mid] == target) {
                return mid;
            }

            if (nums[left] <= nums[mid]) {
                if (nums[left] <= target && target < nums[mid]) {
                    right = mid - 1;
                }
                else {
                    left = mid + 1;
                }
            }
            else {
                if (nums[mid] < target && target <= nums[right]) {
                    left = mid + 1;
                }
                else {
                    right = mid - 1;
                }
            }
        }

        return -1;
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

    std::cout << "target: ";
    int target = 0;
    if (!(std::cin >> target)) return 0;

    int result = solution.search(nums, target);

    std::cout << "result: " << result << std::endl;

    return 0;
}