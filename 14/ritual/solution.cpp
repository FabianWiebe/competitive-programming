//#include <iostream>
#include <vector>
#include <limits>
//#include <fstream>
//#include <algorithm>

#define TESTCASE 2    // 1 = sample, 2 = largeSample,
// ignored on the judge
#include "runner.h"   // This must be *exactly* "runner.h",
// don’t use any other value


using namespace std;

struct Area {
    uint32_t min_x;
    uint32_t min_y;
    uint32_t max_x;
    uint32_t max_y;
};

struct Point {
    uint32_t x;
    uint32_t y;
};

uint32_t stop = 3;
Point reduce_area(Area & a, uint32_t height = numeric_limits<uint32_t>::max(), uint32_t last_x = 0, uint32_t last_y = 0) {
  if (a.max_x - a.min_x < stop && a.max_y - a.min_y < stop) {
    return {last_x, last_y};
  }
  if (a.max_x - a.min_x > a.max_y - a.min_y) {
    uint32_t x = (a.max_x + a.min_x) / 2;
    if (x == last_x) {
      ++x;
    }
    uint32_t min;
    uint32_t min_y;
    bool first = true;
    for (uint32_t y = a.min_y; y <= a.max_y; ++y) {
      uint32_t tmp_min = forest_measure(x, y);
      if (first || tmp_min < min) {
        min = tmp_min;
        min_y = y;
        first = false;
      }
    }
    uint32_t left = forest_measure(x - 1, min_y);
    uint32_t right = forest_measure(x + 1, min_y);
    if (height <= min) {
      // return side of prev found
      if (last_x < x) {
        // left
        a.max_x = x - 1;
      } else {
        // right
        a.min_x = x + 1;
      }
      return reduce_area(a, height, last_x, last_y);
    }
    if (left < min) {
      a.max_x = x - 1;
      return reduce_area(a, left, x - 1, min_y);
    }
    if (right < min) {
      a.min_x = x + 1;
      return reduce_area(a, right, x + 1, min_y);
    }
    a.min_x = x;
    a.max_x = x;
    a.min_y = min_y;
    a.max_y = min_y;
    return {x, min_y};
  } else {
    uint32_t y = (a.max_y + a.min_y) / 2;
    if (y == last_y) {
      ++y;
    }
    uint32_t min;
    uint32_t min_x;
    bool first = true;
    for (uint32_t x = a.min_x; x <= a.max_x; ++x) {
      uint32_t tmp_min = forest_measure(x, y);
      if (first || tmp_min < min) {
        min = tmp_min;
        min_x = x;
        first = false;
      }
    }
    uint32_t top = forest_measure(min_x, y - 1);
    uint32_t bottom = forest_measure(min_x, y + 1);
    if (height <= min) {
      // return side of prev found
      if (last_y < y) {
        // top
        a.max_y = y - 1;
      } else {
        // bottom
        a.min_y = y + 1;
      }
      return reduce_area(a, height, last_x, last_y);
    }
    if (top < min) {
      a.max_y = y - 1;
      return reduce_area(a, top, min_x, y - 1);
    }
    if (bottom < min) {
      a.min_y = y + 1;
      return reduce_area(a, bottom, min_x, y + 1);
    }
    a.min_x = min_x;
    a.max_x = min_x;
    a.min_y = y;
    a.max_y = y;
  }
  return {a.min_x, a.min_y};
}

uint64_t forest_search(uint32_t n) {
  Area a{0, 0, n-1, n-1};
  Point p = reduce_area(a);
  uint32_t current_min = forest_measure(p.x, p.y);
  while (true) {
    // left
    if (p.x > a.min_x) {
      uint32_t tmp = forest_measure(p.x - 1, p.y);
      if (tmp < current_min) {
        current_min = tmp;
        --p.x;
        continue;
      }
    }
    // top
    if (p.y > a.min_y) {
      uint32_t tmp = forest_measure(p.x, p.y-1);
      if (tmp < current_min) {
        current_min = tmp;
        --p.y;
        continue;
      }
    }
    // right
    if (p.x < a.max_x) {
      uint32_t tmp = forest_measure(p.x+1, p.y);
      if (tmp < current_min) {
        current_min = tmp;
        ++p.x;
        continue;
      }
    }
    // bottom
    if (p.y < a.max_y) {
      uint32_t tmp = forest_measure(p.x, p.y+1);
      if (tmp < current_min) {
        current_min = tmp;
        ++p.y;
        continue;
      }
    }
    return forest_encode_solution(p.x, p.y);
  }
}
