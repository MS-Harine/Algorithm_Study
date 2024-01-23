#include <iostream>
using namespace std;

int main() {
  int T, N;
  cin >> T;

  while (T--) {
    cin >> N;
    if (((N + 1) % (N % 100)) == 0)
      cout << "Good" << endl;
    else
      cout << "Bye" << endl;
  }

  return 0;
}