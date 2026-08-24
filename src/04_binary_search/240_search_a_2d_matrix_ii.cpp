// 文件名: 240_search_a_2d_matrix_ii.cpp
// LeetCode 240 - Search a 2D Matrix II
// 难度: Medium
// 提交日期: 2026-08-24
// 解法: 右上角 Z 字形剪枝搜索 (Top-Right Boundary Pruning)
// 时间复杂度: O(M + N)
// 空间复杂度: O(1)

#include <iostream>
#include <vector>

class Solution {
public:
    bool searchMatrix(const std::vector<std::vector<int>>& matrix, int target) {
        if (matrix.empty() || matrix[0].empty()) {
            return false;
        }

        const int m = static_cast<int>(matrix.size());
        const int n = static_cast<int>(matrix[0].size());

        int row = 0;
        int col = n - 1;

        while (row < m && col >= 0) {
            int current = matrix[row][col];

            if (current == target) {
                return true;
            }
            else if (current > target) {
                col--;
            }
            else {
                row++;
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