# Max Points on a Line

LeetCode 45
[ProblemLink](https://leetcode.com/problems/jump-game-ii/description/)

* 23.02.10 CRA Algorithm Study

---
## Problem
You are given a **0-indexed array** of integers `nums` of length `n`. You are initially positioned at `nums[0]`.

Each element `nums[i]` represents the maximum length of a forward jump from index `i`. In other words, if you are at `nums[i]`, you can jump to any `nums[i + j]` where:

- `0 <= j <= nums[i]` and
- `i + j < n`

Return the *minimum number of jumps to reach* `nums[n - 1]`. The test cases are generated such that you can reach `nums[n - 1]`.

<br>

**Example 1**
```
Input: nums = [2,3,1,1,4]
Output: 2
Explanation: The minimum number of jumps to reach the last index is 2. Jump 1 step from index 0 to 1, then 3 steps to the last index.
```

**Eaxmple 2**
```
Input: nums = [2,3,0,1,4]
Output: 2
```

**Constraints**
- `1 <= nums.length <= 10^4`
- `0 <= nums[i] <= 1000`

---
## 문제 풀이
1. `i ~ nums[i]`까지중 최대값을 구해 해당 index로 이동
2. 1번을 반복하며 마지막까지 도착하는 count를 셈

## 개선점
- `i ~ nums[i]`까지 최대값을 구하는 과정에서 이미 한번 계산된 값이 다시 계산되는 과정이 반복됨. DP + Sliding window로 max값을 찾는 과정을 개선할 수 있을 것 같음.
