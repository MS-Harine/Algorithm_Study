#include <iostream>
#include <map>
#include <vector>
#include <string>
using namespace std;

class Stiker {
public:
  char ch;
  int detach;
  int price;

  Stiker(char s, int d, int a): ch(s), detach(d), price(a) {}
};

class StikerString {
public:
  vector<Stiker> st;

  const StikerString& operator+ (const Stiker &other) const {
    StikerString result = *this;
    result += other;
    return result;
  }

  StikerString& operator+=(const Stiker &rhs) {
    Stiker stiker = rhs;
    st.push_back(stiker);
    return *this;
  }

  operator string() const {
    string str = "";
    for (auto iter = st.begin(); iter != st.end(); iter++)
      str += to_string(iter->ch);
    return str;
  }
};

int diffCount(string a, string b) {
  int result = 0;
  for (int i = 0; i < a.length(); i++)
    result += a[i] == b[i] ? 0 : 1;
  return result;
}

int main() {
  int N, M, K;
  cin >> N >> M >> K;

  char s;
  int d, a;

  vector<Stiker> v;
  map<char, vector<Stiker>> m;

  while (M--) {
    cin >> s >> d >> a;
    Stiker st(s, d, a);
    v.push_back(st);

    if (m.find(s) == m.end()) {
      vector<Stiker> vs;
      vs.push_back(st);
      m[s] = vs;
    }
    else
      m[s].push_back(st);
  }

  int idx;
  StikerString ss;
  while (N--) {
    cin >> idx;
    ss += v[idx];
  }

  string target = string(ss);
  string S;
  vector<int> diff;
  cin >> S;

  for (int i = 0; i < S.length() - target.length() + 1; i++)
    diff.push_back(diffCount(target.substr(i, S.length()), S));
}