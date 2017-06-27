#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

static size_t queston_counter = 0;

inline bool ask(size_t first, size_t second, vector<size_t> & correct) {
  ++queston_counter;
//  return correct.at(first) == correct.at(second);
  cout << "q " << first << " " << second << '\n' << flush;
  char anwser;
  cin >> anwser;
  return anwser == 'y';
}

int main (void) {
	std::ios::sync_with_stdio(false);
  std::cin.tie(NULL);
//	 std::ifstream in("largeSample.in");
//	 std::cin.rdbuf(in.rdbuf());
	int total_number;
  vector<unsigned long> prices;
	std::cin >> total_number;
  vector<size_t > inserted;
  size_t counter = 0;
	while (--total_number >= 0) {
    size_t vertices_no;
    cin >> vertices_no;
    // char tmp;
    // cin >> tmp;
    vector<size_t> correct(vertices_no);
//    for (auto itr = correct.begin(); itr != correct.end(); ++itr) {
//      size_t val;
//      cin >> val;
//      *itr = val;
//    }
    using p = pair<size_t, size_t>;
    vector<p> m {{0, 1}};
    for (size_t i = 1; i < vertices_no; ++i) {
      if (m.at(0).second * 3 >= vertices_no * 2) {
        break;
      } else if (m.size() > 1) {
        if (m.at(1).second * 3 > vertices_no) {
          break;
        }
        if ((m.at(0).second + vertices_no - i) * 3 <= vertices_no) {
          break;
        }
        if (m.at(0).second * 3 > vertices_no && (m.at(1).second + vertices_no - i) * 3 <= vertices_no) {
          break;
        }
      }
      bool match = false;
      int tmp_counter = 0;
      for (auto itr = m.begin(); itr != m.end(); ++itr)
      {
        if (tmp_counter++ > 10) {
          match = true;
          break;
        }
        if ((itr->second + vertices_no - i) * 3 <= vertices_no) {
          match = true;
          break;
        }
        if (ask(itr->first, i, correct)) {
          ++itr->second;
          sort(m.begin(), m.end(), [](p & first, p & second) {
            return first.second > second.second;
          });
          match = true;
          break;
        }
      }
      if (!match) {
        m.emplace_back(i, 1);
      }
    }
    // std::cerr << counter++ << ": r";
    // for (auto itr = m.begin(); itr != m.end() && itr->second * 3 > vertices_no; ++itr) {
    //   cerr << " " << itr->first;
    // }
    // cerr << " vertices_no: " << vertices_no << " queston_counter: " << queston_counter << endl;
    queston_counter = 0;
		std::cout << "r";
    for (auto itr = m.begin(); itr != m.end() && itr->second * 3 > vertices_no; ++itr) {
      cout << " " << itr->first;
    }
    cout << endl;
	}
	return 0;
}