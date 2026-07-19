// LeetCode 088 - Merge Sorted Array
// 难度: Easy
// 提交日期: 2026-07-19
// 解法: 双指针·逆向双指针坑位填充型 (Two Pointers - Reverse Fill)
// 时间复杂度: O(m + n) - 仅需单次后向向前线性扫描
// 空间复杂度: O(1) - 零拷贝，利用 nums1 后端预留物理空腔原地归并
//
// ==========================================
// 核心系统设计与性能思考 (AI Infra 视角):
// ==========================================
// 1. 消除正向归并的分配延迟 (Eliminate Allocation Latency):
//    若采取传统正向双指针，必须开辟大小为 O(m+n) 的额外缓冲内存（std::vector），引发堆内存分配（malloc）开销。
//    本算法通过利用 nums1 尾部的有效缓冲空腔，采取“从后往前”的填坑策略，实现了纯粹的零拷贝（Zero-Copy）与 $O(1)$ 内存流转。
//
// 2. 硬件分支预测与逆向顺序写友好 (Branch Prediction & Reverse Sequential Write):
//    在两数组元素交替填入的过程中，由于输入是有序的，CPU 的分支预测器（Branch Predictor）能保持极高命中率。
//    反向遍历直接命中 nums1 分配的高端物理内存块，从大到小对齐，对硬件预取（Hardware Prefetching）和 L1/L2 Cache 写入同样友好。
//
// 3. 边界清理的逻辑门控优化 (Short-Circuit Clean-up Optimization):
//    当 `anum < 0`（nums1 元素耗尽）时，剩余的 nums2 元素必须被整体打扫搬运至前端。
//    若 `bnum < 0`（nums2 元素先耗尽），由于 nums1 原有元素本就处于正确相对位置，算法直接短路切出，省去了无效的自拷贝（memmove）。
//
// ==========================================
// 关键物理内存指针流转图示 (输入: nums1=[1,2,3,0,0,0], m=3, nums2=[2,5,6], n=3):
// ==========================================
// 初始状态: [1,  2,  3,  0,  0,  0]     [2,  5,  6]
//                a               c               b   (a=2, b=2, c=5。nums2[b]=6 > nums1[a]=3 -> nums1[c]=6, b--, c--)
//
// 状态转移: [1,  2,  3,  0,  0,  6]     [2,  5,  6]
//                a           c               b       (nums2[b]=5 > nums1[a]=3 -> nums1[c]=5, b--, c--)
//
// 状态转移: [1,  2,  3,  0,  5,  6]     [2,  5,  6]
//                a       c               b           (nums1[a]=3 > nums2[b]=2 -> nums1[c]=3, a--, c--)
//
// 状态转移: [1,  2,  3,  3,  5,  6]     [2,  5,  6]
//            a       c                   b           (nums2[b]=2 == nums1[a]=2 -> 进入 else 触发 nums1[c]=2, b--, c--)
//
// 打扫战场: [1,  2,  2,  3,  5,  6]     [2,  5,  6]
//            a   c                   b               (bnum=-1 < 0, nums2 耗尽，nums1 前端天然有序，完美收官)
//
// ==========================================

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <limits>

class Solution {
public:
    void merge(std::vector<int>& nums1, int m, std::vector<int>& nums2, int n) {
        int anum = m - 1;       
        int bnum = n - 1;       
        int cnum = m + n - 1;   

        while (anum >= 0 && bnum >= 0) {
            if (nums1[anum] > nums2[bnum]) {
                nums1[cnum] = nums1[anum];
                --anum;
            }
            else {
                nums1[cnum] = nums2[bnum];
                --bnum;
            }
            --cnum;
        }
        while (bnum >= 0) {
            nums1[cnum] = nums2[bnum];
            --bnum;
            --cnum;
        }
    }
};

// ==========================================
// 本地 Debug 测试入口 (展示工程完备性)
// ==========================================
int main() {
    Solution solver;

    int m = 0, n = 0;
    std::cout << "请输入 nums1 的有效元素数量 m: ";
    std::cin >> m;
    std::cout << "请输入 nums2 的有效元素数量 n: ";
    std::cin >> n;

    // 清除输入缓冲区的换行符，防止污染后续 getline
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // 1. 流式解析 nums1 有效元素
    std::cout << "请输入 nums1 的 " << m << " 个有效元素（空格隔开）: ";
    std::string line1;
    std::getline(std::cin, line1);
    std::vector<int> nums1;
    std::stringstream ss1(line1);
    int val;
    while (ss1 >> val) {
        nums1.push_back(val);
    }

    nums1.resize(m + n, 0);

    std::cout << "请输入 nums2 的 " << n << " 个元素（空格隔开）: ";
    std::string line2;
    std::getline(std::cin, line2);
    std::vector<int> nums2;
    std::stringstream ss2(line2);
    while (ss2 >> val) {
        nums2.push_back(val);
    }
    nums2.resize(n); 

    solver.merge(nums1, m, nums2, n);

    std::cout << "\n[归并完成] 物理内存块排序结果: " << std::endl;
    for (int i = 0; i < m + n; ++i) {
        std::cout << nums1[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}