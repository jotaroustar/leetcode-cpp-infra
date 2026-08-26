// 文件名: 658_find_k_closest_elements.cpp
// LeetCode 658 - Find K Closest Elements
// 难度: Medium
// 提交日期: 2026-08-26
// 解法: 窗口左端点二分收敛 (Binary Search for Window Left Bound)
// 时间复杂度: O(log(N - K) + K)
// 空间复杂度: O(1)

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

class Solution {
public:
    std::vector<int> findClosestElements(const std::vector<int>& arr, int k, int x) {
        int left = 0;
        int right = static_cast<int>(arr.size()) - k;

        while (left < right) {
            int mid = left + (right - left) / 2;

            if (x - arr[mid] > arr[mid + k] - x) {
                left = mid + 1;
            }
            else {
                right = mid;
            }
        }

        return std::vector<int>(arr.begin() + left, arr.begin() + left + k);
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

    std::cout << "k: ";
    int k = 0;
    if (!(std::cin >> k)) return 0;

    std::cout << "x: ";
    int x = 0;
    if (!(std::cin >> x)) return 0;

    std::vector<int> result = solution.findClosestElements(arr, k, x);

    std::cout << "result: ";
    for (int num : result) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}