//#include <iostream>
#include <vector>
//#include <fstream>
//#include <algorithm>

#define TESTCASE 1    // 1 = sample, 2 = largeSample,
// ignored on the judge
#include "runner.h"   // This must be *exactly* "runner.h",
// don’t use any other value


using namespace std;

//inline void is_marked(const int x, const int y, const int n, const vector<bool> & checked) {
//  return checked[]
//}

uint64_t forest_search(uint32_t n) {
//  cerr << "n: " << n << endl;
  int x = 0, y = 0;
  if (n == 1) {
    return forest_encode_solution(x, y);
  }
  vector<bool> checked((n + 2) * (n + 2), false);
  for (uint32_t i = 0; i < n + 2; ++i) {
    checked[i] = true;
    checked[(n + 1) * (n + 2) + i] = true;
    checked[i * (n + 2)] = true;
    checked[i * (n + 2) + n + 1] = true;
  }
  x = n/2;
  y = n/2;
  int current_min = forest_measure(x, y);
  checked[x + y * (n + 2)] = true;
  bool found = false;
  while (!found) {
    // left
    if (!checked[(x) + (y+1) * (n + 2)]) {
      checked[(x) + (y+1) * (n + 2)] = true;
      int tmp = forest_measure(x-1, y);
      if (tmp < current_min) {
        current_min = tmp;
        --x;
      }
    // top
    } else if (!checked[(x + 1) + (y) * (n + 2)]) {
      checked[(x + 1) + (y) * (n + 2)] = true;
      int tmp = forest_measure(x, y-1);
      if (tmp < current_min) {
        current_min = tmp;
        --y;
      }
    // right
    } else if (!checked[(x+2) + (y+1) * (n + 2)]) {
      checked[(x+2) + (y+1) * (n + 2)] = true;
      int tmp = forest_measure(x+1, y);
      if (tmp < current_min) {
        current_min = tmp;
        ++x;
      }
    // bottom
    } else if (!checked[(x + 1) + (y +2) * (n + 2)]) {
      checked[(x + 1) + (y+2) * (n + 2)] = true;
      int tmp = forest_measure(x, y+1);
      if (tmp < current_min) {
        current_min = tmp;
        ++y;
      }
    // top left
    } else if (!checked[(x) + (y) * (n + 2)]) {
      checked[(x) + (y) * (n + 2)] = true;
      int tmp = forest_measure(x-1, y-1);
      if (tmp <= current_min) {
        current_min = tmp;
        --x;
        --y;
      }
    // top right
    } else if (!checked[(x + 2) + (y) * (n + 2)]) {
      checked[(x + 2) + (y) * (n + 2)] = true;
      int tmp = forest_measure(x+1, y-1);
      if (tmp <= current_min) {
        current_min = tmp;
        --y;
        ++x;
      }
      // bottom right
    } else if (!checked[(x+2) + (y+2) * (n + 2)]) {
      checked[(x+2) + (y+2) * (n + 2)] = true;
      int tmp = forest_measure(x+1, y+1);
      if (tmp <= current_min) {
        current_min = tmp;
        ++x;
        ++y;
      }
      // bottom left
    } else if (!checked[(x) + (y +2) * (n + 2)]) {
      checked[(x) + (y+2) * (n + 2)] = true;
      int tmp = forest_measure(x-1, y+1);
      if (tmp <= current_min) {
        current_min = tmp;
        ++y;
        --x;
      }
    } else{
      found = true;
      break;
    }
  }
//  std::ios::sync_with_stdio(false);
//  std::cin.tie(NULL);
//	 std::ifstream in("sample.in");
//	 std::cin.rdbuf(in.rdbuf());
  return forest_encode_solution(x, y);
}