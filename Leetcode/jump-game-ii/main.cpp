#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    int jump(vector<int> &nums) {
        if (nums.size() == 1)
            return 0;

        int count = 0, index = 0, max_idx = 0;
        while (index < nums.size() - 1) {
            int max = 0;
            for (int i = index; i <= index + nums[index]; i++) {
                if (i >= nums.size() - 1) {
                    max_idx = nums.size();
                    break;
                }
                if (i + nums[i] > max) {
                    max = i + nums[i];
                    max_idx = i;
                }
            }
            index = max_idx;
            count++;
        }

        return (count == 0) ? 1 : count;
    }
};

int main() {
    vector<int> p1 = {2, 3, 1, 1, 4};
    vector<int> p2 = {2, 3, 0, 1, 4};
    vector<int> p3 = {1, 2, 3};

    Solution s;
    cout << s.jump(p1) << endl;
    cout << s.jump(p2) << endl;
    cout << s.jump(p3) << endl;

    return 0;
}
