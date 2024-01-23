#include <iostream>
#include <vector>
#include <utility>
using namespace std;

class Direction {
public:
  enum Value : int {
    LEFT = 0,
    DOWN = 1,
    RIGHT = 2,
    UP = 3
  };

  Value val;
  Direction() { }
  Direction(Value value) : val(value) { }

  bool operator== (Direction& dir) const { return this->val == dir.val; }
  bool operator== (Direction::Value val) const { return this->val == val; }

  Direction& operator++(int) {
    if (this->val == Direction::LEFT) this->val = Direction::DOWN;
    else if (this->val == Direction::DOWN) this->val = Direction::RIGHT;
    else if (this->val == Direction::RIGHT) this->val = Direction::UP;
    else if (this->val == Direction::UP) this->val = Direction::LEFT;
    return *this;
  }

  Direction operator+(const int n) const {
    Direction dir = (*this);
    dir.val = static_cast<Direction::Value>((static_cast<int>(dir.val) + n) % 4);
    return dir;
  }

  friend ostream& operator<<(ostream& stream, Direction& dir) {
    string str;
    switch (dir.val) {
    case Direction::LEFT:
      str = "LEFT";
      break;
    case Direction::RIGHT:
      str = "RIGHT";
      break;
    case Direction::UP:
      str = "UP";
      break;
    case Direction::DOWN:
      str = "DOWN";
      break;
    }
    return stream << str;
  }
};

class Point {
public:
  int x;
  int y;
  int sand;

  Point() {}
  Point(int nx, int ny, int ns) : x(nx), y(ny), sand(ns), moving_sand(0), moved_sand(0) {}

  Point operator+ (Direction& dir) {
    // cout << "Operator + : " << dir << endl;
    Point p(x, y, sand);
    if (dir == Direction::LEFT) p.x--;
    else if (dir == Direction::DOWN) p.y++;
    else if (dir == Direction::RIGHT) p.x++;
    else if (dir == Direction::UP) p.y--;
    return p;
  }

  int move_tornado(vector<vector<Point>>& map, Direction dir) {
    Direction forward = dir, backward = dir + 2, right = dir + 3, left = dir + 1;
    Point target = (*this) + dir;
    if (target.is_out(map.size()))
      return 0;

    int sum = 0;
    sum += map[target.y][target.x].move_sand(map, target + right, 7);
    sum += map[target.y][target.x].move_sand(map, target + right + right, 2);
    sum += map[target.y][target.x].move_sand(map, target + left, 7);
    sum += map[target.y][target.x].move_sand(map, target + left + left, 2);
    sum += map[target.y][target.x].move_sand(map, target + right + backward, 1);
    sum += map[target.y][target.x].move_sand(map, target + left + backward, 1);
    sum += map[target.y][target.x].move_sand(map, target + right + forward, 10);
    sum += map[target.y][target.x].move_sand(map, target + left + forward, 10);
    sum += map[target.y][target.x].move_sand(map, target + forward + forward, 5);
    sum += map[target.y][target.x].move_sand(map, target + forward, 0, true);
    map[target.y][target.x].update_sand(map);

    return sum;
  }

  bool is_out(int N) {
    return !(this->x >= 0 && this->x < N && this->y >= 0 && this->y < N);
  }

private:
  vector<Point> log;
  int moving_sand;
  int moved_sand;

  void update_sand(vector<vector<Point>>& map) {
    for (auto iter = log.begin(); iter != log.end(); iter++) {
      map[iter->y][iter->x].sand += map[iter->y][iter->x].moving_sand;
      map[iter->y][iter->x].moving_sand = 0;
    }
    map[this->y][this->x].sand = 0;
    map[this->y][this->x].moving_sand = 0;
    log.clear();
    moved_sand = 0;
  }

  int move_sand(vector<vector<Point>>& map, Point to, int percent, bool is_all = false) {
    int val = is_all ? this->sand - this->moved_sand : this->sand * ((double)percent / 100);
    bool valid = !to.is_out(map.size());

    moved_sand += val;
    map[this->y][this->x].moving_sand -= val;
    if (valid && val != 0) {
      map[to.y][to.x].moving_sand += val;
      log.push_back(to);
    }

    // cerr << "From: " << (*this) << " To: " << to << " Percent: " << percent << " Sand: " << val << endl;
    return valid ? 0 : val;
  }

  friend ostream& operator<<(ostream& stream, const Point& p) {
    return stream << "[" << p.x << ", " << p.y << "] (" << p.sand << ")";
  }
};

int main() {
  int N, temp, sand_count = 0;
  vector<vector<Point>> map;

  cin >> N;
  for (int i = 0; i < N; i++) {
    map.push_back(vector<Point>());
    for (int j = 0; j < N; j++) {
      cin >> temp;
      sand_count += temp;
      map[i].push_back(Point(j, i, temp));
    }
  }

  Point cur(N / 2, N / 2, 0);
  Direction dir = Direction::LEFT;
  int dv = 1, dcount = 0;
  int result = 0;
  while (!(dv == N && dcount == 1)) {
    // cerr << "Move from " << cur << " to direction " << dir << " " << dv << endl;
    for (int i = 0; i < dv; i++) {
      result += map[cur.y][cur.x].move_tornado(map, dir);
      cur = cur + dir;
    }

    if (result == sand_count)
      break;

    // for (int i = 0; i < map.size(); i++) {
    //   for (int j = 0; j < map[i].size(); j++)
    //     cout << map[i][j].sand << ' ';
    //   cout << endl;
    // }
    // cout << endl;

    dcount++;
    dir++;
    if (dcount == 2) {
      dcount = 0;
      dv++;
    }
  }

  cout << result << endl;

  return 0;
}