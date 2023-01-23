#include <vector>
#include <map>
#include <limits>
#include <cmath>
#include <iostream>

using namespace std;

class Info {
public:
    double slope;
    double intercept;

    Info(vector<int> p1, vector<int> p2) {
        if (p1[0] == p2[0]) {
            slope = numeric_limits<double>::infinity();
            intercept = p1[0];
        }
        else {
            slope = (double)(p2[1] - p1[1]) / (p2[0] - p1[0]);
            intercept = (double)p2[1] - slope * p2[0];
        }
    }

    bool operator < (const Info &other) const {
        if (isSameFloat(slope, other.slope)) {
            if (isSameFloat(intercept, other.intercept))
                return false;
            else
                return intercept < other.intercept;
        }
        else 
            return slope < other.slope;
    }

private:
    bool isSameFloat(const double n1, const double n2) const {
        if (!isfinite(n1) && !isfinite(n2))
            return true;
        else
            return -1e-4 < (n1 - n2) && (n1 - n2) < 1e-4;
    }
};

class Solution {
public:
    int maxPoints(vector<vector<int>> &points) {
        map<Info, int> m;

        for (int i = 0; i < points.size(); i++) {
            for (int j = 0; j < points.size(); j++) {
                if (i == j)
                    continue;

                Info line(points[i], points[j]);
                if (m.find(line) == m.end()) {
                    m[line] = 1;
                }
                else
                    m[line]++;
            }
        }

        if (m.empty())
            return 1;

        int max = 0;
        for (auto iter = m.begin(); iter != m.end(); iter++) {
            int y = iter->second;
            int count = 0;
            
            int x1 = (1 + (int)sqrt(1 + 4*y)) / 2;
            int x2 = (1 - (int)sqrt(1 + 4*y)) / 2;

            count = x1 < 0 ? x2 : x1;

            if (max < count)
                max = count;
        }

        return max;
    }
};

int main() {
    vector<vector<int>> p1 {{1, 1}, {2, 2}, {3, 3}};
    vector<vector<int>> p2 {{1, 1}, {3, 2}, {5, 3}, {4, 1}, {2, 3}, {1, 4}};
    
    Solution s;
    cout << s.maxPoints(p1) << endl;

    return 0;
}
