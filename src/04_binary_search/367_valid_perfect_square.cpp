// 文件名: 367_valid_perfect_square.cpp
// LeetCode 367 - Valid Perfect Square
// 难度: Easy
// 提交日期: 2026-08-20
// 解法: 数学值域二分精确匹配 (Mathematical Value Range Binary Search)
// 时间复杂度: O(log num)
// 空间复杂度: O(1)

#include <iostream>

class Solution {
public:
    bool isPerfectSquare(int num) {
        if (num < 1) {
            return false;
        }
        if (num == 1) {
            return true;
        }

        int left = 1;
        int right = num / 2;

        while (left <= right) {
            int mid = left + (right - left) / 2;
            long long square = static_cast<long long>(mid) * mid;

            if (square == num) {
                return true;
            }
            else if (square < num) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }

        return false;
    }
};

int main() {
    Solution solution;

    std::cout << "num: ";
    int num = 0;
    if (!(std::cin >> num)) return 0;

    bool result = solution.isPerfectSquare(num);

    std::cout << "result: " << (result ? "true" : "false") << std::endl;

    return 0;
}