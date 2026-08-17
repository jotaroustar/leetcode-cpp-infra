// 文件名: 074_search_a_2d_matrix.cpp
// LeetCode 074 - Search a 2D Matrix
// 难度: Medium
// 提交日期: 2026-08-17
// 解法: 虚拟一维展平坐标映射二分 (Virtual 1D Flattening & Coordinate Projection)
// 时间复杂度: O(log(M * N))
// 空间复杂度: O(1)

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

class Solution {
public:
    bool searchMatrix(const std::vector<std::vector<int>>& matrix, int target) {
        if (matrix.empty() || matrix[0].empty()) {
            return false;
        }

        const int m = static_cast<int>(matrix.size());
        const int n = static_cast<int>(matrix[0].size());

        int left = 0;
        int right = m * n - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            int row = mid / n;
            int col = mid % n;
            int val = matrix[row][col];

            if (val == target) {
                return true;
            }
            else if (val < target) {
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
    int m = 0;
    int n = 0;

    std::cout << "matrix rows (m) and cols (n): ";
    if (!(std::cin >> m >> n) || m <= 0 || n <= 0) return 0;

    std::vector<std::vector<int>> matrix(m, std::vector<int>(n));
    std::cout << "Enter matrix elements (" << m << "x" << n << "):\n";
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cin >> matrix[i][j];
        }
    }

    std::cout << "target: ";
    int target = 0;
    if (!(std::cin >> target)) return 0;

    bool result = solution.searchMatrix(matrix, target);

    std::cout << "result: " << (result ? "true" : "false") << std::endl;

    return 0;
}