#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iterator>
#include <utility>
#include <unordered_map>
#include <fstream>
#include <stdexcept>
#include <unordered_set>
#include <set>

using namespace std;

struct elem {
    size_t value;
    size_t weight;
    elem *prev;
    elem *next;
};


int main (void) {
  std::vector<elem*> al;
  std::ios::sync_with_stdio(false);
  std::cin.tie(NULL);
//	 std::ifstream in("largeSample.in");
//	 std::cin.rdbuf(in.rdbuf());
  int total_number;
  std::cin >> total_number;
  size_t vertices_no, edges_no;
  size_t first, second, weight;
  vector<size_t> stack;
  vector<size_t> counter_in;
  vector<size_t> counter_out;
  vector<size_t> total;
  vector<size_t> amount;
  while (--total_number >= 0) {
    std::cin >> vertices_no;
    edges_no = vertices_no - 1;
    total.clear();
    total.resize(vertices_no, 1);
    amount.clear();
    amount.resize(vertices_no, 0);
    if (edges_no == 0) {
      cout << vertices_no << '\n';
      for (size_t i = 0; i< vertices_no; ++i) {
        cout << i << '\n';
      }
      continue;
    }
    al.clear();
    al.resize(vertices_no, nullptr);
    stack.clear();
    counter_in.clear();
    counter_in.resize(vertices_no, 0);
    counter_out.clear();
    counter_out.resize(vertices_no, 0);
    for (size_t i = 0; i < edges_no; ++i) {
      cin >> first >> second >> weight;
      ++counter_in[second];
      ++counter_out[first];
      if (al[first] == nullptr) {
        al[first] = new elem{second, weight, nullptr, nullptr};
      } else {
        al[first] = new elem{second, weight, nullptr, al[first]};
        al[first]->next->prev = al[first];
      }
    }
    for (size_t i = 0; i < vertices_no; ++i) {
      if (counter_in[i] == 0) {
        stack.push_back(i);
      }
    }
    int current = 0;
    while(true) {
      current = stack.back();
      stack.pop_back();
      if (stack.empty()) {
        break;
      }
      elem* cur = al[current];
      while (cur != nullptr) {
        if (--counter_in[cur->value] == 0) {
          stack.push_back(cur->value);
        }
        amount[cur->value] += amount[current] + total[current] * cur->weight;
        cur = cur->next;
      }
    }
    cout << "" << '\n';
  }
  return 0;
}