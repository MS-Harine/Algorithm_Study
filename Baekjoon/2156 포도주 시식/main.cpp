#include <iostream>
#include <utility>
using namespace std;

void find_minmax(pair<int, int> &a, pair<int, int> &b, pair<int, int> &min, pair<int, int> &max) {
  if (a.first > b.first) {
    max = a;
    min = b;
  }
  else {
    max = b;
    min = a;
  }
}

int main() {
  int n, temp, value, count;
  pair<int, int> drink, nodrink;
  pair<int, int> min, max, new_drink, new_nodrink;

  cin >> n;
  cin >> temp;
  drink = make_pair(temp, 1);
  nodrink = make_pair(0, 0);
  n--;

  while (n--) {
    cout << "[" << drink.first << ", " << drink.second << "] vs [" << nodrink.first << ", " << nodrink.second << "]" << endl;
    cin >> temp;

    find_minmax(drink, nodrink, min, max);
    
    new_drink = make_pair(max.first + temp, max.second + 1);
    if (max.first < min.first + temp)
      new_nodrink = make_pair(min.first + temp, min.second + 1);
    else
      new_nodrink = make_pair(max.first, max.second);

    if (new_drink.second % 3 == 0)
      new_drink.first -= temp;
    
    drink = new_drink;
    nodrink = new_nodrink;
  }

  find_minmax(drink, nodrink, min, max);

  cout << max.first << endl;
  return 0;
}