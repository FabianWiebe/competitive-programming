#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

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
    first_al = 51;
    last_al = 0;
    for (size_t i = 0; i < no_trusses; ++i) {
      size_t first, second;
      cin >> first >> second;
      al[first].push_back(second);
      al[second].push_back(first);
      ++counter[min(first, second)][max(first, second)];
      first_al = min(min(first, second), first_al);
      last_al = max(max(first, second), last_al);
    }

    bool possible = true;

    for (size_t i = first_al; i <= last_al; ++i) {
      if (al[i].size() % 2 == 1) {
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
        size_t tmp_next_val = al[last][next[last]];
        while (next[last] < al[last].size() && (counter[min(last, tmp_next_val)][max(last, tmp_next_val)] == 0)) {
          ++next[last];
          tmp_next_val = al[last][next[last]];
        }
        if (next[last] >= al[last].size()) {
          // reorder
          size_t first_ind;
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
          ++next[last];
          last = tmp_next_val;
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
	}
	return 0;
}