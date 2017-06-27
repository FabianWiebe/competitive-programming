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
     // std::ifstream in("largeSample.in");
     // std::cin.rdbuf(in.rdbuf());
    int total_number;
 
    std::cin >> total_number;
  vector<Point> points;
  vector<Point> shell;
  cout << std::setprecision(3) << std::fixed;
//  vector<Point> bl;
//  vector<Point> br;
//  vector<Point> tr;
//  vector<Point> tl;
    while (--total_number >= 0) {
//    cerr << "begin" << endl;
//    bl.clear();
//    br.clear();
//    tr.clear();
//    tl.clear();
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
 
    int stage = 0;
 
    // 3 | 2
    // -----
    // 0 | 1
 
    shell.push_back(next0);
//    cerr << 3 << ": " << shell.back().first << " " << shell.back().second << '\n';
    Point p = next0;
    Point prev = make_pair(p.first, p.second+1);
 
    double c_length = 0.0;
 
 
 
    while(stage < 4) {
      Point cur_p = make_pair(shell.back().first, shell.back().second);
      Point cur_v = make_pair(cur_p.first - prev.first, cur_p.second - prev.second);
      double max_cos = -1.0 * std::numeric_limits<double>::max();
      unsigned long long int dist = 0;
      if (stage == 0) {
        if (cur_p.second == y_min) {
          ++stage;
        }
      }
      if (stage == 1) {
        if (cur_p.first == x_max) {
          ++stage;
        }
      }
      if (stage == 2) {
        if (cur_p.second == y_max) {
          ++stage;
        }
      }
      if (stage == 3) {
        if (cur_p.first == x_min) {
          break;
        }
      }
      for (auto itr = points.begin(), end = points.end(); itr != end; ++itr) {
        if (stage == 0) {
          if (itr->second >= next0.second || itr->first > next1.first || itr->first < cur_p.first || itr->second > cur_p.second) {
            continue;
          }
        }
        if (stage == 1) {
          if (itr->first <= next1.first || itr->second > next2.second || itr->first < cur_p.first || itr->second < cur_p.second) {
            continue;
          }
        }
        if (stage == 2) {
          if (itr->second <= next2.second || itr->first < next3.first || itr->first > cur_p.first || itr->second < cur_p.second) {
            continue;
          }
        }
        if (stage == 3) {
          if (itr->first >= next3.first || itr->second < next0.second || itr->first > cur_p.first || itr->second > cur_p.second) {
            continue;
          }
        }
//        if (stage != 3) {
//          if (itr->first == p.first && itr->second == p.second) {
//            continue;
//          }
//        }
        Point tmp_v = make_pair(-cur_p.first + itr->first, -cur_p.second + itr->second);
        long long int dot = cur_v.first * tmp_v.first + cur_v.second * tmp_v.second;
//        if (dot < 0) {
//          cerr << "wrong dot < 0" << endl;
//        }
//        dot /= 1 << 16;
        double below = ((1.0*(cur_v.first * cur_v.first+ cur_v.second * cur_v.second))
                             * (1.0*(tmp_v.first * tmp_v.first + tmp_v.second * tmp_v.second)));
        double tmp_cos = 1.0 * dot * dot / below;
        if (dot < 0) {
          tmp_cos *= -1;
        }
 
//        long double tmp_cos = 1.0L * cur_v.first * tmp_v.second / (cur_v.second * tmp_v.first);
//        if (tmp_cos < 0) {
//          tmp_cos *= -1;
//        }
//        if (tmp_cos > 1) {
//          tmp_cos = 1.0L / tmp_cos;
//        }
 
        if (max_cos == -1.0 * std::numeric_limits<double>::max() || tmp_cos > max_cos) {
          max_cos = tmp_cos;
          next = itr;
          dist = tmp_v.first * tmp_v.first + tmp_v.second * tmp_v.second;
        }
        else if (max(tmp_cos, max_cos) - min(tmp_cos, max_cos) < 0.00000000001) {
          unsigned long long int tmp_dist = tmp_v.first * tmp_v.first + tmp_v.second * tmp_v.second;
          if (tmp_dist > dist) {
            next = itr;
            dist = tmp_v.first * tmp_v.first + tmp_v.second * tmp_v.second;
          }
        }
      }
//      if (dist <= 0) {
//        cout << "wrong" << endl;
//      }
      c_length += sqrt(1.0 * dist);
      if (p.first == next->first && p.second == next->second) {
        stage = 5;
        break;
      }
      shell.push_back(*next);
//      cerr << stage << ": " << shell.back().first << " " << shell.back().second << " cos: " << max_cos << " dist: " << sqrt(1.0* dist) << '\n';
      points.erase(next);
      prev = cur_p;
    }
 
//    size_t area = 0;
//    Point first_p = shell[0];
//
//    cerr << "points_no: " << points_no << " shell size: " << shell.size() << '\n';
////    for (auto & p : shell) {
////      cerr << p.first << " " << p.second << '\n';
////    }
//
//
//    Point p_prev = make_pair(shell[1].first - first_p.first, shell[1].second - first_p.second);
//    for (auto itr = shell.begin()+2, end = shell.end(); itr != end; ++itr) {
//      Point p_cur = make_pair(itr->first - first_p.first, itr->second - first_p.second);
//      int tmp_area = p_prev.first * p_cur.second - p_prev.second * p_cur.first;
//      if (tmp_area < 0) {
//        area -= tmp_area;
//      } else {
//        area += tmp_area;
//      }
//      p_prev = p_cur;
//    }
 
 
    cout << c_length << '\n';
    }
    return 0;
}