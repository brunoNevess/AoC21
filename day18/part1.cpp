#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <ranges>
#include <vector>


//////////////////////////
// Hard part of this problem: design the data structure to support all operations and fast query for leftmost and outer most snail numbers
// A Tree was the most appropriate one:
using namespace std;
typedef unsigned long long int ull;
struct Node {
  Node() = default;
  Node(Node &&) = default;
  Node &operator=(Node &&) = default;

  Node(ull value) : left_(nullptr), right_(nullptr), value_(value) {}
  Node(const Node &);
  Node &operator=(const Node &);
  operator ull() const;

private:
  unique_ptr<Node> left_;
  unique_ptr<Node> right_;
  ull value_;

  bool is_terminal() const { return left_ == nullptr && right_ == nullptr; }
  bool explodes();
  bool lr_search(uint32_t dep, optional<ull *> &last_value, optional<ull> &spill);
  bool split();

  istream &operator>>(istream &, Node &);
  ostream &operator<<(ostream &, const Node &);
  Node operator+(const Node &left, const Node &right);
 
  bool one_explode(Node &);
  bool one_split(Node &);
};


istream &operator>>(istream &s, Node &number) {
    char c;
    if (!(s >> c))
      return s;
   
    number.left_ = make_unique<Node>();
    if (s.peek() == '[') {
      s >> *number.left_;
    } else {
      s >> number.left_->value_;
    }
   
    number.right_ = make_unique<Node>();
    if (s.peek() == '[') {
      s >> *number.right_;
    } else {
      s >> number.right_->value_;
    }
   
    return s;
  }
  
  ostream &operator<<(ostream &s, const Node &number) {
    if (number.is_terminal()) {
      s << number.value_;
      return s;
    }
    s << "[" << *number.left_ << "," << *number.right_ << "]";
    return s;
  }
  
  Node operator+(const Node &left, const Node &right) {
    Node result;
    result.left_ = make_unique<Node>(left);
    result.right_ = make_unique<Node>(right);
    do {
      while (result.explodes())
        ;
    } while (result.split());
    return result;
  }
  
  Node::Node(const Node &other) : left_(nullptr), right_(nullptr), value_(other.value_) {
    if (other.is_terminal())
      return;
    left_ = make_unique<Node>(*other.left_);
    right_ = make_unique<Node>(*other.right_);
  }
  
  Node &Node::operator=(const Node &other) {
    if (this == &other)
      return *this;
    if (other.is_terminal()) {
      value_ = other.value_;
      left_ = nullptr;
      right_ = nullptr;
      return *this;
    }
  
    left_ = make_unique<Node>(*other.left_);
    right_ = make_unique<Node>(*other.right_);
    return *this;
  }
  
  Node::operator ull() const {
    if (is_terminal())
      return value_;
    return 3 * static_cast<ull>(*left_) + 2 * static_cast<ull>(*right_);
  }
  
  bool Node::explodes() {
    optional<ull> spill;
    optional<ull *> last_value;
    return lr_search(0, last_value, spill) || spill.has_value();
  }
  
  bool Node::lr_search(uint32_t dep, optional<ull *> &last_value, optional<ull> &spill) {
    if (is_terminal()) {
      if (spill.has_value()) {
        value_ += spill.value();
        spill.reset();
        return true;
      }
  
      last_value = &value_;
      return false;
    }
  
    if (dep < 4 || spill.has_value() || !left_->is_terminal() || !right_->is_terminal()) {
      return left_->lr_search(dep + 1, last_value, spill) || right_->lr_search(dep + 1, last_value, spill);
    }
  
    if (last_value.has_value()) {
      (*last_value.value()) += left_->value_;
    }
    spill = right_->value_;
    left_ = nullptr;
    right_ = nullptr;
    value_ = 0;
    return false;
  }
  
  bool Node::split() {
    if (!is_terminal()) {
      if (left_->split())
        return true;
      return right_->split();
    }
  
    if (value_ < 10)
      return false;
  
    left_ = make_unique<Node>(value_ / 2);
    right_ = make_unique<Node>((value_ + 1) / 2);
    return true;
}

////////////////////////////////////////

int main(int argc, char *argv[]) {
  string input;
  cin >> input;
  vector<Node> numbers;
  ranges::copy(ranges::istream_view<Node>(input), back_inserter(numbers));
  Node sum = accumulate(numbers.begin() + 1, numbers.end(), numbers[0], plus<>());
  cout << "Part 1: " << (ull)sum << "\n";

  ull best = 0;
  // brute force
  for (int i = 0; i < numbers.size(); i++) {
    for (int j = i + 1; j < numbers.size(); j++) {
      best = max({best, (numbers[i] + numbers[j]), (numbers[j] + numbers[i])});
    }
  }
  cout << "Part 2: " << best << "\n";
}