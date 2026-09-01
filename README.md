# LeetCode 练习题

我的 LeetCode 刷题记录，目标：备战日本 IT 企业技术面试。

## 详细资料

* **累计完成**：45 题
* **目标**：2027年3月份前完成 200 题，覆盖日本 IT 面试常考专题
* **编程语言**：C++ (C++17 标准)

---

| 题号 | 题目 | 难易度 | 解法 / 核心机制 | 提交日期 | 状态 |
| --- | --- | --- | --- | --- | --- |
| 001 | [两数之和](https://leetcode.cn/problems/two-sum/) | Easy | 哈希表（Single-pass Hash Map） | 07-17 | Pass |
| 003 | [无重复字符的最长子串](https://leetcode.cn/problems/longest-substring-without-repeating-characters/) | Medium | 跳跃式滑动窗口 + ASCII 直接映射（Sliding Window + ASCII Direct Mapping） | 08-03 | Pass |
| 011 | [盛最多水的容器](https://leetcode.cn/problems/container-with-most-water/) | Medium | 对撞双指针（Min Height Shrink, Spatial Pruning） | 07-21 | Pass |
| 019 | [删除链表的倒数第 N 个结点](https://leetcode.cn/problems/remove-nth-node-from-end-of-list/) | Medium | 哨兵哑节点 + 双指针定距收敛（Sentinel Dummy Node & Fast-Slow Gap Pointers） | 08-29 | Pass |
| 020 | [有效的括号](https://leetcode.cn/problems/valid-parentheses/) | Easy | 辅助栈（Stack Matching / ASCII Direct Mapping） | 07-22 | Pass |
| 021 | [合并两个有序链表](https://leetcode.cn/problems/merge-two-sorted-lists/) | Easy | 哨兵哑节点 + 双指针归并（Sentinel Dummy Node & Two-Pointer Merge） | 08-28 | Pass |
| 024 | [两两交换链表中的节点](https://leetcode.cn/problems/swap-nodes-in-pairs/) | Medium | 哨兵哑节点 + 三指针就地重连（Sentinel Dummy Node & In-Place Pointer Rewiring） | 08-30 | Pass |
| 026 | [删除有序数组中的重复项](https://leetcode.cn/problems/remove-duplicates-from-sorted-array/) | Easy | 同向双指针（Fast/Slow Pointer） | 07-16 | Pass |
| 027 | [移除元素](https://leetcode.cn/problems/remove-element/) | Easy | 同向双指针（Fast/Slow Pointer） | 07-18 | Pass |
| 033 | [搜索旋转排序数组](https://leetcode.cn/problems/search-in-rotated-sorted-array/) | Medium | 局部有序二分查找（Interval Monotonicity Discrimination） | 08-14 | Pass |
| 034 | [在排序数组中查找元素的第一个和最后一个位置](https://leetcode.cn/problems/find-first-and-last-position-of-element-in-sorted-array/) | Medium | 双重二分边界收敛（Lower/Upper Bound Convergence, O(1) Space） | 08-13 | Pass |
| 035 | [搜索插入位置](https://leetcode.cn/problems/search-insert-position/) | Easy | 二分查找边界收敛（Lower Bound Convergence） | 08-12 | Pass |
| 069 | [x 的平方根](https://leetcode.cn/problems/sqrtx/) | Easy | 数学值域二分截断（Mathematical Value Range Binary Search） | 08-19 | Pass |
| 074 | [搜索二维矩阵](https://leetcode.cn/problems/search-a-2d-matrix/) | Medium | 虚拟一维展平坐标映射二分（Virtual 1D Flattening & Coordinate Projection） | 08-17 | Pass |
| 084 | [柱状图中最大的矩形](https://leetcode.cn/problems/largest-rectangle-in-histogram/) | Hard | 单调递增栈 + 首尾双哨兵（Monotonic Increasing Stack, Double Sentinels） | 07-29 | Pass |
| 088 | [合并两个有序数组](https://leetcode.cn/problems/merge-sorted-array/) | Easy | 逆向双指针（Tail Pointer, Zero-Copy） | 07-19 | Pass |
| 092 | [反转链表 II](https://leetcode.cn/problems/reverse-linked-list-ii/) | Medium | 哨兵哑节点 + 头插法单趟穿针引线（Sentinel Dummy Node & In-Place Head Insertion） | 09-01 | Pass |
| 142 | [环形链表 II](https://leetcode.cn/problems/linked-list-cycle-ii/) | Medium | 快慢指针相遇 + 同速追赶法（Floyd's Cycle-Finding Algorithm） | 08-31 | Pass |
| 150 | [逆波兰表达式求值](https://leetcode.cn/problems/evaluate-reverse-polish-notation/) | Medium | 栈操作引擎 + 分支优化（Stack-Based Evaluation Engine, Branch-Friendly Dispatch） | 08-01 | Pass |
| 153 | [寻找旋转排序数组中的最小值](https://leetcode.cn/problems/find-minimum-in-rotated-sorted-array/) | Medium | 右端点基准单调性收敛（Right-Bound Pivot Convergence） | 08-15 | Pass |
| 155 | [最小栈](https://leetcode.cn/problems/min-stack/) | Medium | 状态增强单栈（State-Augmented Single Stack, Cache Friendly） | 07-23 | Pass |
| 162 | [寻找峰值](https://leetcode.cn/problems/find-peak-element/) | Medium | 梯度爬坡单调收敛（Gradient Ascent Binary Search） | 08-16 | Pass |
| 167 | [两数之和 II - 输入有序数组](https://leetcode.cn/problems/two-sum-ii-input-array-is-sorted/) | Medium | 对撞双指针（Opposite Collision, O(1) Space） | 07-20 | Pass |
| 206 | [反转链表](https://leetcode.cn/problems/reverse-linked-list/) | Easy | 双指针迭代就地反转（Iterative In-Place Pointer Inversion） | 08-27 | Pass |
| 209 | [长度最小的子数组](https://leetcode.cn/problems/minimum-size-subarray-sum/) | Medium | 变长滑动窗口（Aggressive Shrink Loop, Zero-Allocation） | 08-04 | Pass |
| 225 | [用队列实现栈](https://leetcode.cn/problems/implement-stack-using-queues/) | Easy | 单队列环形旋转（Single-Queue Ring Rotation, Cache Friendly） | 07-25 | Pass |
| 232 | [用栈实现队列](https://leetcode.cn/problems/implement-queue-using-stacks/) | Easy | 双栈模拟（Dual-Stack, Amortized O(1) Time） | 07-24 | Pass |
| 239 | [滑动窗口最大值](https://leetcode.cn/problems/sliding-window-maximum/) | Hard | 单调双端队列（Monotonic Deque Engine, Zero-Allocation Output） | 08-02 | Pass |
| 240 | [搜索二维矩阵 II](https://leetcode.cn/problems/search-a-2d-matrix-ii/) | Medium | 右上角 Z 字形剪枝搜索（Top-Right Boundary Pruning） | 08-24 | Pass |
| 367 | [有效的完全平方数](https://leetcode.cn/problems/valid-perfect-square/) | Easy | 数学值域二分精确匹配（Mathematical Value Range Binary Search） | 08-20 | Pass |
| 424 | [替换后的最长重复字符](https://leetcode.cn/problems/longest-repeating-character-replacement/) | Medium | 滑动窗口 + 历史最高频次单调不降（Monotonic Max Frequency, Zero-Allocation） | 08-08 | Pass |
| 438 | [找到字符串中所有字母异位词](https://leetcode.cn/problems/find-all-anagrams-in-a-string/) | Medium | 定长滑动窗口 + 栈上固定频次表（Fixed-Size Window, Zero-Allocation Vectorization） | 08-05 | Pass |
| 496 | [下一个更大元素 I](https://leetcode.cn/problems/next-greater-element-i/) | Easy | 单调递减栈 + 哈希表预处理（Monotonic Stack, Hash Map Preprocessing） | 07-30 | Pass |
| 503 | [下一个更大元素 II](https://leetcode.cn/problems/next-greater-element-ii/) | Medium | 单调递减栈 + 虚拟双倍数组（Monotonic Decreasing Stack, Virtual Double-Length Array） | 07-28 | Pass |
| 540 | [有序数组中的单一元素](https://leetcode.cn/problems/single-element-in-a-sorted-array/) | Medium | 奇偶索引对齐二分（Parity-Aligned Index Binary Search） | 08-25 | Pass |
| 567 | [字符串的排列](https://leetcode.cn/problems/permutation-in-string/) | Medium | 定长滑动窗口 + 栈上固定频次表（Fixed-Size Window, Zero-Allocation Vectorization） | 08-09 | Pass |
| 658 | [找到 K 个最接近的元素](https://leetcode.cn/problems/find-k-closest-elements/) | Medium | 窗口左端点二分收敛（Binary Search for Window Left Bound） | 08-26 | Pass |
| 704 | [二分查找](https://leetcode.cn/problems/binary-search/) | Easy | 标准双闭区间二分查找（Standard Closed Interval Binary Search） | 08-10 | Pass |
| 739 | [每日温度](https://leetcode.cn/problems/daily-temperatures/) | Medium | 单调递减栈（Monotonic Decreasing Stack, Cache Friendly） | 07-27 | Pass |
| 744 | [寻找比目标字母大的最小字母](https://leetcode.cn/problems/find-smallest-letter-greater-than-target/) | Easy | 环形边界上界收敛（Circular Upper Bound Convergence） | 08-21 | Pass |
| 852 | [山脉数组的峰顶索引](https://leetcode.cn/problems/peak-index-in-a-mountain-array/) | Medium | 山脉单调性梯度二分（Mountain Peak Gradient Binary Search） | 08-22 | Pass |
| 875 | [爱吃香蕉的珂珂](https://leetcode.cn/problems/koko-eating-bananas/) | Medium | 值域二分答案 + 判定性单调谓词（Binary Search on Answer） | 08-18 | Pass |
| 904 | [水果成篮](https://leetcode.cn/problems/fruit-into-baskets/) | Medium | 变长滑动窗口（At Most K Distinct Types, Bounded Map Footprint） | 08-07 | Pass |
| 1004 | [最大连续1的个数 III](https://leetcode.cn/problems/max-consecutive-ones-iii/) | Medium | 变长滑动窗口（Tolerance Budget Mechanism, Zero-Allocation） | 08-06 | Pass |
| 1047 | [删除字符串中的所有相邻重复项](https://leetcode.cn/problems/remove-all-adjacent-duplicates-in-string/) | Easy | 隐式字符串栈（In-Place String Stack Engine, Zero-Allocation） | 07-31 | Pass |