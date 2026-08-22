// 文件名: 852_peak_index_in_a_mountain_array.cpp
// LeetCode 852 - Peak Index in a Mountain Array
// 难度: Medium
// 提交日期: 2026-08-22
// 解法: 山脉单调性梯度二分 (Mountain Peak Gradient Binary Search)
// 时间复杂度: O(log N)
// 空间复杂度: O(1)

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

class Solution {
public:
    int peakIndexInMountainArray(const std::vector<int>& arr) {
        int left = 1;
        int right = static_cast<int>(arr.size()) - 2;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (arr[mid] > arr[mid + 1]) {
                right = mid - 1;
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

    std::cout << "arr: ";
    if (!std::getline(std::cin, line) || line.empty()) return 0;

    std::stringstream ss(line);
    std::vector<int> arr;
    int val = 0;
    while (ss >> val) {
        arr.push_back(val);
    }

    int result = solution.peakIndexInMountainArray(arr);

    std::cout << "result: " << result << std::endl;

    return 0;
}