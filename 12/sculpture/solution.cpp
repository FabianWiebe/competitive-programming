#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

//template <typename T>
//struct Entry {
//    Entry(T v, Entry<T> * p = nullptr) : value(std::move(v)), nodes(1u), parent(p), is_root(true) {
//      if (!parent) {
//        this->parent = this;
//      } else {
//        ++(this->parent->nodes);
//        this->is_root = false;
//      }
//    }
//    T value;
//    size_t nodes;
//    Entry<T> * parent;
//    bool is_root;
//    Entry<T> * get_representative() {
//      if (this->is_root) {
//        return this;
//      }
//      return this->parent = this->parent->get_representative();
//    }
//    inline bool is_in_same_set(Entry<T> * e) {
//      return this->get_representative() == e->get_representative();
//    }
//    inline bool merge (Entry<T> * e) {
//      if (this->is_in_same_set(e)) {
//        return false;
//      }
//      // parent = get_representative()
//      if (e->parent->nodes > this->parent->nodes) {
//        e->parent->nodes += this->parent->nodes;
//        this->parent->is_root = false;
//        this->parent->parent = e->parent;
//      } else {
//        this->parent->nodes += e->parent->nodes;
//        e->parent->is_root = false;
//        e->parent->parent = this->parent;
//      }
//      return true;
//    }
//};
//
//using entry = Entry<int>;
using Pair = pair<size_t, size_t>;

int main (void) {
//	std::ios::sync_with_stdio(false);
//  std::cin.tie(NULL);
//	 std::ifstream in("sample.in");
//	 std::cin.rdbuf(in.rdbuf());
	int total_number;
	std::cin >> total_number;
  vector<size_t> al[51];
  size_t counter[51][51];
//  entry* uf[51];
  size_t next[51];
  size_t case_counter = 0;
  size_t first_al = 0;
  size_t last_al = 51;
	while (--total_number >= 0) {
    size_t no_trusses;
		std::cin >> no_trusses;
    for (auto & list : al) {
      list.clear();
    }
    for (size_t i = first_al; i < last_al; ++i) {
      for (size_t j = i; j < last_al; ++j) {
        counter[i][j] = 0;
      }
    }
//    for (size_t i = 0; i < 51; ++i) {
//      uf[i] = new entry(i);
//    }
    first_al = 51;
    last_al = 0;
    for (size_t i = 0; i < no_trusses; ++i) {
      size_t first, second;
      cin >> first >> second;
//      --first;
//      --second;
      al[first].push_back(second);
      al[second].push_back(first);
//      uf[first]->merge(uf[second]);
      ++counter[min(first, second)][max(first, second)];
      first_al = min(min(first, second), first_al);
      last_al = max(max(first, second), last_al);
    }

    bool possible = true;

//    entry * representative = uf[first_al]->get_representative();
    for (size_t i = first_al; i <= last_al; ++i) {
      if (al[i].size() % 2 == 1) { //  || (!al[i].empty() && uf[i]->get_representative() != representative)
        possible = false;
        break;
      }
      next[i] = 0;
    }
    cout << "Case #" << ++case_counter << '\n';
//    cerr << "Case #" << case_counter << '\n';
    if (possible) {
      vector<Pair> out;
      out.reserve(no_trusses);
      size_t last = first_al;
      while (out.size() < no_trusses) {
        size_t tmp_next = next[last];
        size_t tmp_next_val = al[last][tmp_next];
        while (tmp_next < al[last].size() && (counter[min(last, tmp_next_val)][max(last, tmp_next_val)] == 0)) {
          ++tmp_next;
          tmp_next_val = al[last][tmp_next];
        }
        if (tmp_next >= al[last].size()) {
          // reorder
          size_t first_ind;
          next[last] = tmp_next;
          bool found = false;
          for (first_ind = 1; first_ind < out.size(); ++first_ind) {
            if (next[out[first_ind].first] < al[out[first_ind].first].size()) {
              found = true;
              break;
            }
          }
          if (!found) {
            possible = false;
            break;
          }
          vector<Pair> tmp(out.size());
          copy(out.begin() + first_ind, out.end(), tmp.begin());
          copy(out.begin(), out.begin() + first_ind, tmp.begin() + (out.size() - first_ind));
          out = tmp;
          last = out[0].first;
        } else {
          // insert
          out.emplace_back(last, tmp_next_val);
          --counter[min(last, tmp_next_val)][max(last, tmp_next_val)];
          next[last] = tmp_next + 1;
          last = al[last][tmp_next];
        }
      }
      if (possible) {
        for (auto & pair : out) {
          cout << pair.first <<  ' ' << pair.second << '\n';
  //        cerr << pair.first <<  ' ' << pair.second << '\n';
        }
      } else {
        cout << "some trusses may be lost" << '\n';
      }
    } else {
      cout << "some trusses may be lost" << '\n';
//      cerr << "some trusses may be lost" << '\n';
    }
    cout << endl;
//    cerr << '\n';
//    for (auto ptr : uf) {
//      delete ptr;
//    }
	}
	return 0;
}