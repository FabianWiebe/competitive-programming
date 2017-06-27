#include <iostream>
#include <vector>
#include <fstream>
#include <utility>
#include <algorithm>
#include <iomanip>
#include <limits>
#include <cmath>

using namespace std;

using Point = pair<long long, long long>;

int main (void) {
	std::ios::sync_with_stdio(false);
  std::cin.tie(NULL);
	  std::ifstream in("tmp.txt");
	  std::cin.rdbuf(in.rdbuf());
	int total_number;

	std::cin >> total_number;
  vector<Point> points;
  vector<Point> shell;
  cout << std::setprecision(3) << std::fixed;
  vector<Point> split_points[4];
	while (--total_number >= 0) {
    for (auto & split_point : split_points) {
      split_point.clear();
    }
    size_t points_no;
    int x, y;
		std::cin >> points_no;
    points.resize(points_no);
    shell.clear();
    int x_min = std::numeric_limits<int>::max();
    vector<Point>::iterator next;
    Point next0;
    int x_max = -1;
    Point next1;
    int y_min = std::numeric_limits<int>::max();
    Point next2;
    int y_max = -1;
    Point next3;
    for (auto itr = points.begin(), end = points.end(); itr != end; ++itr) {
      cin >> x >> y;
      *itr = make_pair(x, y);
      if (x < x_min || (x == x_min && y > next0.second)) {
        x_min = x;
        next0 = *itr;
      }
      if (y_min > y || (y == y_min && x < next1.first)) {
        y_min = y;
        next1 = *itr;
      }
      if (x_max < x || (x == x_max && y < next2.second)) {
        x_max = x;
        next2 = *itr;
      }
      if (y_max < y || (y == y_max && x > next3.first)) {
        y_max = y;
        next3 = *itr;
      }
    }
    for (auto itr = points.begin(), end = points.end(); itr != end; ++itr) {
        if (itr->second < next0.second && itr->first <= next1.first) {
            split_points[0].push_back(*itr);
        }
        if (itr->first > next1.first && itr->second <= next2.second) {
          split_points[1].push_back(*itr);
        }
        if (itr->second > next2.second && itr->first >= next3.first) {
          split_points[2].push_back(*itr);
        }
        if (itr->first < next3.first && itr->second >= next0.second) {
          split_points[3].push_back(*itr);
        }
    }
    sort(split_points[0].begin(), split_points[0].end(), [](const Point & p1, const Point & p2) {
        if (p1.first == p2.first) {
          return p1.second > p2.second;
        }
        return p1.first < p2.first;
    });
    sort(split_points[1].begin(), split_points[1].end(), [](const Point & p1, const Point & p2) {
        if (p1.first == p2.first) {
          return p1.second < p2.second;
        }
        return p1.first < p2.first;
    });
    sort(split_points[2].begin(), split_points[2].end(), [](const Point & p1, const Point & p2) {
        if (p1.first == p2.first) {
          return p1.second < p2.second;
        }
        return p1.first > p2.first;
    });
    sort(split_points[3].begin(), split_points[3].end(), [](const Point & p1, const Point & p2) {
        if (p1.first == p2.first) {
          return p1.second > p2.second;
        }
        return p1.first > p2.first;
    });


    int stage = 0;

    // 3 | 2
    // -----
    // 0 | 1

    shell.push_back(next0);
//    cerr << 3 << ": " << shell.back().first << " " << shell.back().second << '\n';
    Point p = next0;
    Point prev = make_pair(p.first, p.second+1);

    double c_length = 0.0;

    auto beg_itr = split_points[stage].begin();
    while(stage < 4) {
      Point cur_p = make_pair(shell.back().first, shell.back().second);
      Point cur_v = make_pair(cur_p.first - prev.first, cur_p.second - prev.second);
      double max_cos = -1.0 * std::numeric_limits<double>::max();
      unsigned long long int dist = 0;
      if (stage == 0) {
        if (cur_p.second == y_min) {
          ++stage;
          beg_itr = split_points[stage].begin();
        }
      }
      if (stage == 1) {
        if (cur_p.first == x_max) {
          ++stage;
          beg_itr = split_points[stage].begin();
        }
      }
      if (stage == 2) {
        if (cur_p.second == y_max) {
          ++stage;
          beg_itr = split_points[stage].begin();
        }
      }
      if (stage == 3) {
        if (cur_p.first == x_min) {
          break;
        }
      }
      for (auto itr = beg_itr, end = split_points[stage].end(); itr != end; ++itr) {
        Point tmp_v = make_pair(itr->first - cur_p.first, itr->second - cur_p.second);
        long long int dot = cur_v.first * tmp_v.first + cur_v.second * tmp_v.second;
        double below = ((1.0*(cur_v.first * cur_v.first+ cur_v.second * cur_v.second))
                             * (1.0*(tmp_v.first * tmp_v.first + tmp_v.second * tmp_v.second)));
        double tmp_cos = 1.0 * dot * dot / below;
        if (dot < 0) {
          tmp_cos *= -1;
        }

        if (max_cos == -1.0 * std::numeric_limits<double>::max() || tmp_cos > max_cos) {
          max_cos = tmp_cos;
          next = itr;
          dist = tmp_v.first * tmp_v.first + tmp_v.second * tmp_v.second;
          beg_itr = itr;
        } else if (max(tmp_cos, max_cos) - min(tmp_cos, max_cos) < 0.00000000001) {
          unsigned long long int tmp_dist = tmp_v.first * tmp_v.first + tmp_v.second * tmp_v.second;
          if (tmp_dist > dist) {
            next = itr;
            dist = tmp_v.first * tmp_v.first + tmp_v.second * tmp_v.second;
            beg_itr = itr;
          }
        }
      }
      c_length += sqrt(1.0 * dist);
      if (p.first == next->first && p.second == next->second) {
        stage = 5;
        break;
      }
      shell.push_back(*next);
//      cerr << stage << ": " << shell.back().first << " " << shell.back().second << " cos: " << max_cos << " dist: " << sqrt(1.0* dist) << '\n';
//      split_points[stage].erase(next);
      prev = cur_p;
      ++beg_itr;
    }

    cout << c_length << '\n';
	}
	return 0;
}