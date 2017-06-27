#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

int main (void) {
	std::ios::sync_with_stdio(false);
  std::cin.tie(NULL);
//	 std::ifstream in("largeSample.in");
//	 std::cin.rdbuf(in.rdbuf());
	int total_number;
  vector<vector<bool>> map;
  vector<vector<size_t>> prev;
	std::cin >> total_number;
	while (--total_number >= 0) {
    size_t w, h;
    char c;
    cin >> w >> h;
    map.clear();
    map.resize(h+2);
    map.front().resize(w+2);
    map.back().resize(w+2);
    prev.clear();
    prev.resize(h+2, vector<size_t>(w+2));
    for (auto itr = ++map.begin(), end = --map.end(); itr != end; ++itr) {
      itr->resize(w+2);
      for (auto i_itr = ++itr->begin(), i_end = --itr->end(); i_itr != i_end; ++i_itr) {
        cin >> c;
        *i_itr = c == 'f';
      }
    }
    size_t current_max = 0;
    for (size_t i = 1; i < h+1; ++i) {
      for (size_t j = 1; j < w+1; ++j) {
        if(map[i][j]) {
          prev[i][j] = min(min(prev[i-1][j-1], prev[i-1][j]), prev[i-1][j+1]) + 1;
          if (prev[i][j] > current_max) {
            current_max = prev[i][j];
          }
        }
      }
    }
    prev.clear();
    prev.resize(h+2, vector<size_t>(w+2));
    for (size_t i = h+1; i > 0; --i) {
      for (size_t j = 1; j < w+1; ++j) {
        if(map[i][j]) {
          prev[i][j] = min(min(prev[i+1][j-1], prev[i+1][j]), prev[i+1][j+1]) + 1;
          if (prev[i][j] > current_max) {
            current_max = prev[i][j];
          }
        }
      }
    }
    prev.clear();
    prev.resize(h+2, vector<size_t>(w+2));
    for (size_t i = 1; i < w+1; ++i) {
      for (size_t j = 1; j < h+1; ++j) {
        if(map[j][i]) {
          prev[j][i] = min(min(prev[j-1][i-1], prev[j][i-1]), prev[j+1][i-1]) + 1;
          if (prev[j][i] > current_max) {
            current_max = prev[j][i];
          }
        }
      }
    }
    prev.clear();
    prev.resize(h+2, vector<size_t>(w+2));
    for (size_t i = w+1; i > 0; --i) {
      for (size_t j = 1; j < h+1; ++j) {
        if(map[j][i]) {
          prev[j][i] = min(min(prev[j-1][i+1], prev[j][i+1]), prev[j+1][i+1]) + 1;
          if (prev[j][i] > current_max) {
            current_max = prev[j][i];
          }
        }
      }
    }


		std::cout << (current_max * current_max) << '\n';
	}
	return 0;
}