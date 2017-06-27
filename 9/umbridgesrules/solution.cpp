#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <algorithm>
#include <limits>
#include <cstdlib>

using namespace std;
using Point = pair<int, int>;
Point null_point = make_pair(-1, -1);
//std::array<Point, 4> null_points = {null_point}; //, {-1,-1}, {-1,-1}, {-1,-1}}; //{null_point, null_point, null_point, null_point};
int y_max = -1;
int y_min = std::numeric_limits<int>::max();

inline unsigned long long int dist(const Point & p1, const Point & p2) {
  return 1llu * (p1.first - p2.first) * (p1.first - p2.first)
             + 1llu * (p1.second - p2.second) * (p1.second - p2.second);
}

vector<Point> l1;
vector<Point> l2;
vector<Point> r1;
vector<Point> r2;

unsigned long long int find_shortest_path(vector<Point> & points, size_t start_id, size_t end_id) {
  const size_t range = end_id - start_id;
  if (range < 2) {
    return dist(points[start_id], points[end_id]);
  } else if (range < 3) {
    return min(min(dist(points[start_id], points[end_id]),dist(points[start_id+1], points[end_id])), dist(points[start_id], points[start_id+1]));
  }
  size_t mid_id = (end_id + start_id) / 2;
  const Point & middle = points[mid_id];
  unsigned long long int n_min = min(find_shortest_path(points, start_id, mid_id), find_shortest_path(points, mid_id + 1, end_id));
//  if (abs(n_min - 5.40059e+09) < 1000000) {
//    cerr << "wrong" << endl;
//    for (size_t i = start_id; i <= end_id; ++i) {
//      for (size_t j = start_id; j <= end_id; ++j) {
//        cerr << points[i].first << " " << points[i].second << "   ,   " << points[j].first << " " << points[j].second;
//        cerr << " : " << dist(points[i], points[j]) << endl;
//      }
//    }
//    cerr  << "end" << endl;
//  }
  long double _min = sqrt(n_min);
  if (_min + middle.first <= points[mid_id+1].first) {
    return n_min;
  }
  const size_t tmp_size = (y_max-y_min+1)/ _min * 2;
  size_t x_min = middle.first - _min / 2;
  size_t x_max = ceil(middle.first + _min / 2);
  l1.clear();
  l2.clear();
  r1.clear();
  r2.clear();
  l1.resize(tmp_size, null_point);
  l2.resize(tmp_size, null_point);
  r1.resize(tmp_size, null_point);
  r2.resize(tmp_size, null_point);
  int i;
  for (i = mid_id; i >= 0; --i) {
    if (points[i].first > x_min) {
      l2[ceil(1.0 * points[i].second/_min)] = points[i];
    } else {
      break;
    }
  }
  x_min = middle.first - _min;
  for (; i >= 0; --i) {
    if (points[i].first > x_min) {
      l1[ceil(1.0 * points[i].second/_min)] = points[i];
    } else {
      break;
    }
  }
  for (i = mid_id  + 1; i <= end_id ; ++i) {
    if (points[i].first < x_max) {
      r1[ceil(1.0 * points[i].second/_min)] = points[i];
    } else {
      break;
    }
  }
  x_max = ceil(middle.first + _min);
  for (; i <= end_id ; ++i) {
    if (points[i].first < x_max) {
      r2[ceil(1.0 * points[i].second/_min)] = points[i];
    } else {
      break;
    }
  }
  Point p1, p2;
  for (i = 0; i < tmp_size; ++i) {
    if (l1[i].first != -1) {
      for (int j = -2; j <= 2; ++j) {
        if (i + j >= 0 && i + j < tmp_size && r1[i+j].first != -1) {
          unsigned long long int tmp = dist(l1[i], r1[i+j]);
          if (tmp > n_min) {
            p1 = l1[i];
            p2 = r1[i+j];
          }
          n_min = min(n_min, tmp);
        }
      }
    }
    if (l2[i].first != -1) {
      for (int j = -2; j <= 2; ++j) {
        if (i + j >= 0 && i + j < tmp_size) {
          if (r1[i+j].first != -1) {
            unsigned long long int tmp = dist(l2[i], r1[i+j]);
            if (tmp > n_min) {
              p1 = l2[i];
              p2 = r1[i+j];
            }
            n_min = min(n_min, dist(l2[i], r1[i + j]));
          }
          if (r2[i+j].first != -1) {
            unsigned long long int tmp = dist(l2[i], r2[i+j]);
            if (tmp > n_min) {
              p1 = l2[i];
              p2 = r2[i+j];
            }
            n_min = min(n_min, dist(l2[i], r2[i + j]));
          }
        }
      }
    }
  }
//  int test = round(sqrt(n_min)*100);
//  if (abs(n_min - 5.40059e+09) < 1000000) { // abs(n_min - 246381.0) < 100
//    cout << p1.first << " " << p1.second << " ,  " << p2.first << " " << p2.second << endl;
////    cerr << "wrong" << endl;
//  }
  return n_min;
}

int main (void) {
	std::ios::sync_with_stdio(false);
  std::cin.tie(NULL);
//	 std::ifstream in("sample.in");
//	 std::cin.rdbuf(in.rdbuf());
	int total_pupil;
  cin >> total_pupil;
  unordered_map<size_t, vector<Point>> pupils;
  bool not_easy = false;
  for (size_t i = 0; i < total_pupil; ++i) {
    int x, y, floor;
    cin >> x >> y >> floor;
    if (x >= 100000 || y >= 100000) {
      not_easy = true;
    }
    if (y > y_max) {
      y_max = y;
    }
    if (y < y_min) {
      y_min = y;
    }
    pupils[floor].emplace_back(x, y);
  }
  unsigned long long int shortest_dist = std::numeric_limits<unsigned long long int>::max();

//  cerr << pupils.size() << endl;
	for (auto & p : pupils) {
//    if (p.first != 14) {
//      continue;
//    }
    auto v = p.second;
    if (v.size() < 2) {
      continue;
    }
    if(total_pupil < 20000) { //  && pupils.size() == 1
      for (auto & p1 : v) {
        for (auto & p2 : v) {
          if (p1.first != p2.first || p1.second != p2.second) {
            shortest_dist = min(shortest_dist, dist(p1, p2));
          }
        }
      }
    } else {

//      cerr << p.first << " " << v.size();
      sort(v.begin(), v.end(), [](const Point & p1, const Point & p2) {
         return p1.first < p2.first;
      });
      unsigned long long int tmp = find_shortest_path(v, 0, v.size()-1);
//      cerr << " " << tmp << endl;

      shortest_dist = min(shortest_dist, tmp);
    }
  }

  size_t result = round(sqrt(shortest_dist)*100);

  std::cout << result << endl;
	return 0;
}