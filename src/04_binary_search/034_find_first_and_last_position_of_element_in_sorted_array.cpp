// LeetCode 034 - Find First and Last Position of Element in Sorted Array
// 难度: Medium
// 提交日期: 2026-08-13
// 解法: 双重二分边界收敛 (Lower Bound & Upper Bound Deconstruction)
// 时间复杂度: O(log N)
// 空间复杂度: O(1)

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

class Solution {
private:
    int lowerBound(const std::vector<int>& nums, long long target) {
        int left = 0;
        int right = static_cast<int>(nums.size()) - 1;
        int ans = static_cast<int>(nums.size());

        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] >= target) {
                ans = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return ans;
    }

public:
    std::vector<int> searchRange(const std::vector<int>& nums, int target) {
        const int n = static_cast<int>(nums.size());

        int first = lowerBound(nums, target);

        if (first == n || nums[first] != target) {
            return {-1, -1};
        }

        int last = lowerBound(nums, static_cast<long long>(target) + 1) - 1;

        return {first, last};
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

    std::vector<int> result = solution.searchRange(nums, target);

    std::cout << "result: [" << result[0] << ", " << result[1] << "]" << std::endl;

    return 0;
}