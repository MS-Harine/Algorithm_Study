#include <iostream>
#include <string>
#include <cmath>

using namespace std;

bool t_n(int n, int t, int l);
bool t_n_2(int n, int t, int l);
bool t_n_3(int n, int t, int l);
bool t_2_n(int n, int t, int l);
bool t_n_f(int n, int t, int l);

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int C;
  bool (*func)(int, int, int);
  cin >> C;

  while (C--) {
    string S;
    int N, T, L;

    cin >> S >> N >> T >> L;
    if (!S.compare("O(N)")) {
      func = t_n;
    }
    else if (!S.compare("O(N^2)")) {
      func = t_n_2;
    }
    else if (!S.compare("O(N^3)")) {
      func = t_n_3;
    }
    else if (!S.compare("O(2^N)")) {
      func = t_2_n;
    }
    else {
      func = t_n_f;
    }

    cout << (func(N, T, L) ? "May Pass." : "TLE!") << endl;
  }

  return 0;
}

bool t_n(int n, int t, int l) {
  return n * t <= l * 1e8;
}

bool t_n_2(int n, int t, int l) {
  if (n >= 31623)
    return false;
  
  return pow(n, 2) <= (double)l / t * 1e8;
}

bool t_n_3(int n, int t, int l) {
  if (n > 1000)
    return false;
  
  return pow(n, 3) <= (double)l / t * 1e8;
}

bool t_2_n(int n, int t, int l) {
  if (n >= 30)
    return false;
  
  return pow(2, n) <= (double)l / t * 1e8;
}

bool t_n_f(int n, int t, int l) {
  if (n >= 13)
    return false;
  
  long f = 1;
  for (int i = 0; i < n; i++)
    f *= (n - i);

  return f < (double)l / t * 1e8;
}