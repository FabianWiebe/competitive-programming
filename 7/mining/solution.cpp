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
    elem *prev;
    elem *next;
    elem *other;
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
  vector<size_t> counter;
  vector<size_t> with;
  vector<size_t> without;
	while (--total_number >= 0) {
		std::cin >> vertices_no;
    edges_no = vertices_no - 1;
    with.resize(vertices_no);
    without.resize(vertices_no);
    for (size_t i = 0; i < vertices_no; ++i) {
      cin >> weight;
      with[i] = 2 * weight;
      without[i] = weight;
    }
    if (edges_no == 0) {
      cout << to_string(without[0]) << '\n';
      continue;
    }
    al.clear();
    al.resize(vertices_no, nullptr);
    stack.clear();
    counter.clear();
    counter.resize(vertices_no, 0);
		for (size_t i = 0; i < edges_no; ++i) {
			cin >> first >> second;
      ++counter[first];
      ++counter[second];
      if (al[first] == nullptr) {
        al[first] = new elem{second, nullptr, nullptr, nullptr};
      } else {
        al[first] = new elem{second, nullptr, al[first], nullptr};
        al[first]->next->prev = al[first];
      }
      if (al[second] == nullptr) {
        al[second] = new elem{first, nullptr, nullptr, al[first]};
      } else {
        al[second] = new elem{first, nullptr, al[second], al[first]};
        al[second]->next->prev = al[second];
      }
      al[first]->other = al[second];
		}
    for (size_t i = 0; i < vertices_no; ++i) {
      if (counter[i] == 1) {
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
      --counter[current];
      elem *tmp = al[current];
      size_t next = tmp->value;
      if (--counter[next] == 1) {
        stack.push_back(next);
      }
      if (tmp->next == nullptr && tmp->prev == nullptr) {
        al[current] = nullptr;
      } else {
        if (tmp->next != nullptr) {
          tmp->next->prev = tmp->prev;
        }
        if (tmp->prev != nullptr) {
          tmp->prev->next = tmp->next;
        } else {
          al[current] = tmp->next;
        }
      }
      tmp = tmp->other;
      delete tmp->other;
      if (tmp->next == nullptr && tmp->prev == nullptr) {
        al[next] = nullptr;
      } else {
        if (tmp->next != nullptr) {
          tmp->next->prev = tmp->prev;
        }
        if (tmp->prev != nullptr) {
          tmp->prev->next = tmp->next;
        } else {
          al[next] = tmp->next;
        }
      }
      delete tmp;
      with[next] += without[current];
      without[next] += std::max(with[current], without[current]);
    }
    cout << std::max(with[current], without[current])/2 << '\n';
	}
	return 0;
}