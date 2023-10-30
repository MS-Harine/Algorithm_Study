#include <iostream>
#include <algorithm>

using namespace std;

void countChar(int (&arr)[4], char ch, bool isMinus = false) {
    switch (ch) {
    case 'A':
        isMinus ? arr[0]-- : arr[0]++;
        break;
    case 'C':
        isMinus ? arr[1]-- : arr[1]++;
        break;
    case 'G':
        isMinus ? arr[2]-- : arr[2]++;
        break;
    case 'T':
        isMinus ? arr[3]-- : arr[3]++;
        break;
    }
}

bool checkCount(int A, int C, int G, int T, int (&count)[4]) {
    return (count[0] >= A) && (count[1] >= C) && (count[2] >= G) && (count[3] >= T);
}

int main() {
    int s, p;
    string str;
    int A, C, G, T;
    int count[4] = {0, 0, 0, 0};
    int result = 0;

    cin >> s >> p;
    cin.ignore();
    cin >> str;
    cin.ignore();
    cin >> A >> C >> G >> T;

    for (int i = 0; i < min((int)str.length(), p); i++)
        countChar(count, str[i]);
    
    if (checkCount(A, C, G, T, count))
        result++;

    for (int i = 1; i <= str.size() - p; i++) {
        countChar(count, str[i - 1], true);
        countChar(count, str[i + p - 1]);

        if (checkCount(A, C, G, T, count))
            result++;
    }

    cout << result << endl;
    return 0;
}