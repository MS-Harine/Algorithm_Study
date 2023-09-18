#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

class Person {
  int id;
  int score;
  int n_correct;
  vector<bool> correct;
  vector<int> n_fail;

public:
  Person() {}
  Person(int id, int M) {
    this->id = id;
    score = 0;
    n_correct = 0;
    correct.assign(M, false);
    n_fail.assign(M, 0);
  }

  bool is_correct(int m) {
    return correct[m];
  }

  void set_correct(int m, int t) {
    correct[m] = true;
    n_correct++;
    score += t + n_fail[m] * 20;
  }

  void set_fail(int m) {
    n_fail[m]++;
  }

  bool operator < (const Person& other) const {
    int n_problem = accumulate(correct.begin(), correct.end(), 0);
    int other_n_problem = accumulate(other.correct.begin(), other.correct.end(), 0);

    bool result = n_problem > other_n_problem;
    if (n_problem == other_n_problem)
      result = score < other.score;
    return result;
  }

  friend ostream& operator << (ostream& outs, const Person &p ) {
    return outs << p.id << ' ' << p.n_correct << ' ' << p.score;
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int K;
  cin >> K;

  for (int k = 1; k <= K; k++) {
    int M, N, P;

    cin >> M >> N >> P;
    Person *people = new Person[P];
    for (int i = 0; i < P; i++)
      people[i] = Person(i + 1, M);

    while (N--) {
      int p, t, j;
      char m;

      cin >> p >> m >> t >> j;

      int person = p - 1, problem = m - 'A';

      if (people[person].is_correct(problem))
        continue;
      
      if (j == 1)
        people[person].set_correct(problem, t);
      else
        people[person].set_fail(problem);
    }

    sort(people, people + P);

    cout << "Data Set " << k << ':' << endl;
    for (int i = 0; i < P; i++)
      cout << people[i] << endl;
    cout << endl;
    
    delete[] people;
  }

  return 0;
}