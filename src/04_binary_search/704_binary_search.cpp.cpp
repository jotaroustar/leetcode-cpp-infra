// LeetCode 704 - Binary Search
// 难度: Easy
// 提交日期: 2026-08-10
// 解法: 标准双闭区间二分查找 (Standard Closed Interval Binary Search)
// 时间复杂度: O(log N) - 对数级收敛
// 空间复杂度: O(1) - Zero Dynamic Allocation
//
// ==========================================
// 核心系统设计与性能思考 (AI Infra 视角):
// ==========================================
// 1. 标准双闭区间收敛 ([left, right]):
//    无复杂边界偏移，命中 target 即刻中断返回，是最基础且绝对安全的二分模版。
//
// 2. 整型溢出防御 (Numeric Overflow Protection):
//    采用 left + (right - left) / 2 计算 mid，防止 (left + right) 超过 INT_MAX。
// ==========================================

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

class Solution {
public:
    int search(const std::vector<int>& nums, int target) {
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

        return -1; 
    }
};

// ==========================================
// 本地 Debug 测试入口 (支持自定义交互输入)
// ==========================================
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

    int result = solution.search(nums, target);

    std::cout << "result: " << result << std::endl;

    return 0;
}