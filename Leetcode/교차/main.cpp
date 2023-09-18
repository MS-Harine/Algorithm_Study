#include <iostream>
#include <vector>
#include <utility>
using namespace std;

int main() {
    int N;
    int x_start, y_start, x_end, y_end, left, top, right, bottom;
    int y_max, y_min;
    
    vector<pair<int, int>> points;
    double slope, intercept;
    bool result;
    int area = 0;
    char ch;

    cin >> N;
    while (N--) {
        result = false;
        area = 0;

        cin >> x_start >> y_start >> x_end >> y_end;
        cin >> left >> top >> right >> bottom;
        y_max = y_start < y_end ? y_end : y_start;
        y_min = y_start < y_end ? y_start : y_end;

        if (x_start == x_end) {
            if ((left - x_start) * (right - x_start) < 0)
                cout << "T" << endl;
            else
                cout << "F" << endl;
            continue;
        }
        
        points.push_back(make_pair(left, top));
        points.push_back(make_pair(left, bottom));
        points.push_back(make_pair(right, top));
        points.push_back(make_pair(right, bottom));

        if (y_end == y_start)
            slope = 0;
        else
            slope = (double)(x_end - x_start) / (y_end - y_start);
        intercept = y_start - slope * x_start;

        while (!points.empty()) {
            pair<int, int> point = points.back();
            points.pop_back();

            double value = point.first * slope + intercept;
            if (value == point.second) {
                result = true;
                points.clear();
            }
            else if (value < point.second) {
                if (area > 0 && (y_min < value & value < y_max)) {
                    result = true;
                    points.clear();
                }
                else
                    area = -1;
            }
            else {
                if (area < 0 && (y_min < value & value < y_max)) {
                    result = true;
                    points.clear();
                }
                else
                    area = 1;
            }
        }

        ch = result ? 'T' : 'F';
        cout << ch << endl;
    }
}