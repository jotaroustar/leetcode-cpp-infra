// 文件名: 744_find_smallest_letter_greater_than_target.cpp
// LeetCode 744 - Find Smallest Letter Greater Than Target
// 难度: Easy
// 提交日期: 2026-08-21
// 解法: 环形边界上界收敛 (Circular Upper Bound Convergence)
// 时间复杂度: O(log N)
// 空间复杂度: O(1)

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

class Solution {
public:
    char nextGreatestLetter(const std::vector<char>& letters, char target) {
        int left = 0;
        int right = static_cast<int>(letters.size()) - 1;
        int ans = 0;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (letters[mid] > target) {
                ans = mid;
                right = mid - 1;
            }
            else {
                left = mid + 1;
            }
        }

        return letters[ans];
    }
};

int main() {
    Solution solution;
    std::string line;

    std::cout << "letters: ";
    if (!std::getline(std::cin, line) || line.empty()) return 0;

    std::stringstream ss(line);
    std::vector<char> letters;
    char ch = '\0';
    while (ss >> ch) {
        letters.push_back(ch);
    }

    std::cout << "target: ";
    char target = '\0';
    if (!(std::cin >> target)) return 0;

    char result = solution.nextGreatestLetter(letters, target);

    std::cout << "result: " << result << std::endl;

    return 0;
}