#include <iostream>
using namespace std;

class MarbleTree {
public:
  MarbleTree(int n): num_nodes(n), div(1), rem(0) {
    nodes = new Node[n + 1];
    root = &nodes[1];
  }
  ~MarbleTree() { delete[] nodes; }

  int find_elem(uint64_t num) {
    Node *cur = this->root;
    
    while (!cur->is_leaf()) {
      if (cur->has_both()) {
        if (is_left(num)) {
          set_left();
          cur = cur->get_left();
        }
        else {
          set_right();
          cur = cur->get_right();
        }
      }
      else
        cur = cur->get_child();
    }

    return cur->num;
  }

  void set_child(int parent, int left, int right) {
    nodes[parent].num = parent;
    nodes[parent].left = left == -1 ? nullptr : &nodes[left];
    nodes[parent].right = right == -1 ? nullptr : &nodes[right];
  }

private:
  class Node {
  public:
    int num;
    Node *left;
    Node *right;
    bool has_both() { return this->left && this->right; }
    bool is_leaf() { return !(this->left || this->right); }
    Node * get_left() { return this->left; }
    Node * get_right() { return this->right; }
    Node * get_child() {
      return this->left ? this->left : this->right;
    }
  };

private:
  bool is_right(uint64_t n) {
    int d = this->div * 2;
    int r = this->rem;

    return (n + r) % d == 0;
  }
  void set_right() {
    this->div = this->div * 2;
  }

  bool is_left(uint64_t n) {
    int d = this->div * 2;
    int r = this->div + this->rem;

    return (n + r) % d == 0;
  }
  void set_left() {
    this->rem = this->div + this->rem;
    this->div = this->div * 2;
  }

  int num_nodes;
  int div, rem;
  Node *root;
  Node *nodes;
};

int main() {
  int N, l, r;
  uint64_t K;
  cin >> N;

  MarbleTree mt(N);
  for (int i = 1; i <= N; i++) {
    cin >> l >> r;
    mt.set_child(i, l, r);
  }

  cin >> K;
  cout << mt.find_elem(K) << endl;

  return 0;
}