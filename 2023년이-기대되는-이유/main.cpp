#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <set>
#include <cmath>
#include <cstring>
using namespace std;

// Code from https://doomed-lab.tistory.com/56
void _decompose(vector<vector<int>> &result, int n, int k, vector<int> &subset) {
    if (k == n + 1)
        result.push_back(subset);
    else {
        subset.push_back(k);
        _decompose(result, n, k + 1, subset);
        subset.pop_back();
        _decompose(result, n, k + 1, subset);
    }
}

vector<vector<int>> decompose(int size) {
    static map<int, vector<vector<int>>> memory;

    vector<vector<int>> decompose_result;
    vector<int> subset;

    auto find = memory.find(size);
    if (find == memory.end()) {
        _decompose(decompose_result, size - 1, 1, subset);
        memory.insert(make_pair(size, decompose_result));
    }
    else
        decompose_result = find->second;
    
    return decompose_result;
}

set<int> getSummation(string n) {
    set<int> result;
    vector<vector<int>> decompose_result = decompose(n.size());
    
    for (auto iter = decompose_result.begin(); iter != decompose_result.end(); iter++) {
        vector<int> combination = *iter;
        int sum = 0;
        for (int i = 0; i <= combination.size(); i++) {
            int begin_index = (i == 0) ? 0 : combination[i - 1];
            int end_index = (i == combination.size()) ? n.size() : combination[i];
            
            sum += stoi(n.substr(begin_index, end_index - begin_index));
        }
        result.insert(sum);
    }

    return result;
}

int main() {
    int T = 0;
    string n;

    cin >> T;
    while (T--) {
        cin >> n;

        vector<int> num;
        int origin_num = stoi(n);
        for (int i = 0; i < n.size(); i++)
            num.push_back(n[i] - '0');
        

        set<int> sum_list = getSummation(n);
        
        int m = 0;
        long prev = 0;
        for (int power = 1; ; power++) {
            long sum = 0;
            for (auto iter = num.begin(); iter != num.end(); iter++)
                sum += pow(*iter, power);
            
            if (sum > origin_num)
                break;
            else if (sum == prev) {
                m = -1;
                break;
            }

            if (sum_list.find(sum) != sum_list.end())
                m++;
            prev = sum;
        }

        if (m == -1)
            cout << "Hello, BOJ 2023!" << endl;
        else
            cout << m << endl;
    }
}