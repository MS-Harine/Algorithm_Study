# Max Points on a Line

LeetCode 149
[ProblemLink](https://leetcode.com/problems/max-points-on-a-line/)

* 23.01.17 CRA Algorithm Study
* To be updated

---
## Problem
Given an array of `points` where `points[i] = [xi, yi]` represents a point on the **X-Y** plane, return _the maximum number of points that lie on the same straight line._

## Example
![ex1](https://assets.leetcode.com/uploads/2021/02/25/plane1.jpg)
```
Input: points = [[1,1],[2,2],[3,3]]
Output: 3
```
![ex1](https://assets.leetcode.com/uploads/2021/02/25/plane2.jpg)
```
Input: points = [[1,1],[3,2],[5,3],[4,1],[2,3],[1,4]]
Output: 4
```

## Constraints
* `1 <= points.length <= 300`
* `points[i].length == 2`
* `-10^4 <= x_i, y_i <= 10^4`
* All the `points` are **unique**

---
## 문제 풀이
1. 같은 라인에 있는 점인지 파악하기 위해 두 점의 기울기 및 y절편을 모두 구한다. _(Line 14 ~ 23)_

2. 같은 라인에 있는 두 점의 개수를 모두 센다. _(Line 50 ~ 62)_

3. 같은 라인에 있는 두 점의 개수는 `n * (n-1)`개이다. 이를 역으로 `n`을 구한다. _(Line 68 ~ 79)_

## 개선점
* 모든 라인의 기울기 및 절편을 구하고 시작하는 것이 아닌, 한 점을 기준으로 다른 점들에 모두 선을 그어 같은 라인에 있는 점의 개수의 최대값을 구해나가면 memory 아낄 수 있음.
