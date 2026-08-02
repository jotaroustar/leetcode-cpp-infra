// LeetCode 239 - Sliding Window Maximum
// 难度: Hard
// 提交日期: 2026-08-02
// 解法: 单调双端队列 (Monotonic Deque Engine)
// 时间复杂度: O(n) - 每个元素最多入队和出队一次
// 空间复杂度: O(k) - 双端队列最多维护 k 个元素的索引
//
// ==========================================
// 核心系统设计与性能思考 (AI Infra 视角):
// ==========================================
// 1. 单调队列算子 (Monotonic Deque Engine):
//    摒弃 std::priority_queue 的 O(N log K) 堆重构开销，利用单调队列维护窗口内“单调递减”的候选最大值索引。
//    实现严格 O(1) 平摊状态转移（每个下标最多进/出队列一次）。
//
// 2. 下标存储与边界判定 (Index-based Tracking):
//    队列内仅存储元素数组下标 i 而非具体数值。一方面天然解决数值重复问题，
//    另一方面便于根据 front_index <= i - k 在 O(1) 时间内准确清除过期 (Out of Window) 节点。
//
// 3. 内存预分配 (Zero-Allocation Output):
//    结果数组大小已知为 nums.size() - k + 1，预先调用 reserve() 彻底杜绝 vector 扩容带来的内存拷贝开销。
// ==========================================

#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <sstream>

class Solution {
public:
    std::vector<int> maxSlidingWindow(const std::vector<int>& nums, int k) {
        const int n = static_cast<int>(nums.size());
        if (n == 0 || k <= 0) return {};
        std::vector<int> result;
        result.reserve(n - k + 1);

        std::deque<int> dq;

        for (int i = 0; i < n; ++i) {
            if (!dq.empty() && dq.front() <= i - k) {
                dq.pop_front();
            }
            while (!dq.empty() && nums[dq.back()] <= nums[i]) {
                dq.pop_back();
            }

            dq.push_back(i);

            if (i >= k - 1) {
                result.push_back(nums[dq.front()]);
            }
        }

        return result;
    }
};

// ==========================================
// 本地 Debug 测试入口 (终端交互)
// ==========================================
int main() {
    std::cout << "请输入数组元素（空格隔离）: ";
    std::string line;
    std::getline(std::cin, line);

    std::stringstream ss(line);
    std::vector<int> nums;
    int num = 0;
    while (ss >> num) {
        nums.push_back(num);
    }

    std::cout << "请输入滑动窗口大小 k: ";
    int k = 0;
    std::cin >> k;

    if (nums.empty() || k <= 0 || k > static_cast<int>(nums.size())) {
        std::cout << "输入参数无效（数组为空或 k 超出合理范围）。" << std::endl;
        return 0;
    }

    Solution solution;
    std::vector<int> ans = solution.maxSlidingWindow(nums, k);

    std::cout << "\n--- 计算结果 (滑动窗口最大值) ---" << std::endl;
    std::cout << "滑动窗口最大值序列: [ ";
    for (int val : ans) {
        std::cout << val << " ";
    }
    std::cout << "]" << std::endl;
    std::cout << "------------------------------------------" << std::endl;

    return 0;
}