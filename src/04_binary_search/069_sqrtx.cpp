// 文件名: 069_sqrtx.cpp
// LeetCode 069 - Sqrt(x)
// 难度: Easy
// 提交日期: 2026-08-19
// 解法: 数学值域二分截断 (Mathematical Value Range Binary Search)
// 时间复杂度: O(log x)
// 空间复杂度: O(1)

#include <iostream>

class Solution {
public:
    int mySqrt(int x) {
        if (x == 0 || x == 1) {
            return x;
        }

        int left = 1;
        int right = x / 2;
        int ans = 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (static_cast<long long>(mid) * mid <= x) {
                ans = mid;
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }

        return ans;
    }
};

int main() {
    Solution solution;

    std::cout << "x: ";
    int x = 0;
    if (!(std::cin >> x)) return 0;

    int result = solution.mySqrt(x);

    std::cout << "result: " << result << std::endl;

    return 0;
}