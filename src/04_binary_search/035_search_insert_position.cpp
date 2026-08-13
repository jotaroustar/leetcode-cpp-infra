// LeetCode 035 - Search Insert Position
// 难度: Easy
// 提交日期: 2026-08-12
// 解法: 二分查找边界收敛 (Lower Bound)
// 时间复杂度: O(log N)
// 空间复杂度: O(1)

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

class Solution {
public:
    int searchInsert(const std::vector<int>& nums, int target) {
        int left = 0;
        int right = static_cast<int>(nums.size()) - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] == target) {
                return mid;
            }
            else if (nums[mid] < target) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
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

    std::cout << "target: ";
    int target = 0;
    if (!(std::cin >> target)) return 0;

    int result = solution.searchInsert(nums, target);

    std::cout << "result: " << result << std::endl;

    return 0;
}