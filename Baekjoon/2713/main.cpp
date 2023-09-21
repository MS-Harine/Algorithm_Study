#include <iostream>
#include <string>
#include <vector>

using namespace std;

string char2bin(char ch) {
  if (ch == ' ')
    ch = 'A' - 1;
  ch = ch - 'A' + 1;

  string result = "";
  while (ch != 0) {
    result = (char)(ch % 2 + '0') + result;
    ch /= 2;
  }

  while (result.length() != 5)
    result = '0' + result;

  return result;
}

string rearrange(string str, int R, int C) {
  int i = 0, j = 0, top = 0, left = -1;
  enum Direction { RIGHT, DOWN, LEFT, UP };
  Direction dir = RIGHT;

  vector<vector<char>> map(R, vector<char>(C, '0'));
  for (int idx = 0; idx < str.length(); idx++) {
    map[i][j] = str.at(idx);
    switch (dir) {
    case RIGHT:
      j++;
      if (j == C) {
        j--;
        i++;
        dir = DOWN;
        C--;
      }
      break;
    case DOWN:
      i++;
      if (i == R) {
        i--;
        j--;
        dir = LEFT;
        R--;
      }
      break;
    case LEFT:
      j--;
      if (j == left) {
        j++;
        i--;
        dir = UP;
        left++;
      }
      break;
    case UP:
      i--;
      if (i == top) {
        i++;
        j++;
        dir = RIGHT;
        top++;
      }
      break;
    }
  }

  string result = "";
  for (int i = 0; i < map.size(); i++)
    for (int j = 0; j < map[i].size(); j++)
      result += map[i][j];
  return result;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int T;
  cin >> T;

  while (T--) {
    int R, C;
    char msg;
    string encrypt = "";

    cin >> R >> C;
    cin.ignore();
    while((msg = cin.get()) != '\n')
      encrypt += char2bin(msg);

    cout << rearrange(encrypt, R, C) << endl;
  }

  return 0;
}