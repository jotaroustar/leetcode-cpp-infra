// 文件名: 875_koko_eating_bananas.cpp
// LeetCode 875 - Koko Eating Bananas
// 难度: Medium
// 提交日期: 2026-08-18
// 解法: 值域二分答案 + 判定性单调谓词 (Binary Search on Answer)
// 时间复杂度: O(N * log(max(Piles)))
// 空间复杂度: O(1)

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

class Solution {
private:
    bool canFinish(const std::vector<int>& piles, int h, int k) {
        long long totalHours = 0;
        for (int pile : piles) {
            totalHours += (static_cast<long long>(pile) + k - 1) / k;
        }
        return totalHours <= h;
    }

public:
    int minEatingSpeed(const std::vector<int>& piles, int h) {
        int left = 1;
        int right = *std::max_element(piles.begin(), piles.end());
        int ans = right;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (canFinish(piles, h, mid)) {
                ans = mid;
                right = mid - 1;
            }
            else {
                left = mid + 1;
            }
        }

        return ans;
    }
};

int main() {
    Solution solution;
    std::string line;

    std::cout << "piles: ";
    if (!std::getline(std::cin, line) || line.empty()) return 0;

    std::stringstream ss(line);
    std::vector<int> piles;
    int val = 0;
    while (ss >> val) {
        piles.push_back(val);
    }

    std::cout << "h: ";
    int h = 0;
    if (!(std::cin >> h)) return 0;

    int result = solution.minEatingSpeed(piles, h);

    std::cout << "result: " << result << std::endl;

    return 0;
}