#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <fstream>
#include <list>
#include <cmath>
#include <algorithm>
#include <stdexcept>

using namespace std;

struct Point {
    Point(int x_, int y_, int id_) : x(x_), y(y_), id(id_) {}
    int x;
    int y;
    int id;
};

inline int distance(const Point & p1, const Point & p2) {
  return abs(p1.x - p2.x) + abs(p1.y - p2.y);
}

//struct Elem {
//    Elem(int id_, Elem* next_) : id(id_), next(next_) {}
//    int id;
//    Elem * next;
//};

int main (void) {
	std::ios::sync_with_stdio(false);
  std::cin.tie(NULL);
//  	    std::ifstream ins("largeSample.in");
//      std::cin.rdbuf(ins.rdbuf());
	int counter;
	std::cin >> counter;
  vector<Point> vec_points;
  vec_points.reserve(11);
  int dist_p[11][11];
  int ind[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	while (--counter >= 0) {
    int x_size, y_size, coins_no, x, y;
    cin >> x_size >> y_size;
    cin >> x >> y;
    vec_points.clear();
    vec_points.emplace_back(x, y, 0);
    cin >> coins_no;
    for (int i = 1; i <= coins_no; ++i) {
      cin >> x >> y;
      vec_points.emplace_back(x, y, i);
    }
//    sort(vec_points.begin(), vec_points.end(), [](const Point & p1, const Point & p2) {
//      return p1.x < p2.x;
//    });
//    ++coins_no;
//    sort(vec_points.begin(), vec_points.begin() + coins_no/2, [](const Point & p1, const Point & p2) {
//      return p1.y < p2.y;
//    });
//    sort(vec_points.begin() + coins_no/2, vec_points.end(), [](const Point & p1, const Point & p2) {
//        return p1.y > p2.y;
//    });
    for (const auto & point1 : vec_points) {
      for (const auto & point2 : vec_points) {
        dist_p[point1.id][point2.id] = distance(point1, point2);
      }
    }
//    vector<int> ind;
//    ind.reserve(coins_no);
//    for (int i = 0; i < coins_no; ++i) {
//      ind.push_back(i);
//    }
    int sum = std::numeric_limits<int>::max();
    do {
      int tmp_sum = dist_p[ind[0]][ind[coins_no]];
      for (int i = 0; i < coins_no && tmp_sum < sum; ++i) {
        tmp_sum += dist_p[ind[i]][ind[i+1]];
      }
      if (tmp_sum < sum) {
        sum = tmp_sum;
      }
    } while ( std::next_permutation(ind, ind+coins_no) );

//    Elem* last = new Elem(vec_points.back().id, nullptr);
//    Elem* current = last;
//    for (auto ritr = vec_points.rbegin()+1; ritr != vec_points.rend(); ++ritr) {
//      current = new Elem(ritr->id, current);
//    }
//    last->next = current;
//    Elem* next = last;
//
//    bool found;
//    if (coins_no > 3) {
//      do {
//        found = false;
//        current = next;
//        auto rem = current;
//        do {
////          int rem_next_id = rem->next->id;
//          int saved_dist = dist_p[rem->id][rem->next->next->id] - dist_p[rem->id][rem->next->id] - dist_p[rem->next->id][rem->next->next->id];
////          int saved_dist = dist_p[rem->id][rem->next->next->id] - dist[rem->id][rem->next->id][rem->next->next->id];
//
//          for (auto ins = rem->next->next; ins != rem; ins = ins->next) {
//            int current_dist = saved_dist - dist_p[ins->id][ins->next->id] + dist_p[ins->id][rem->next->id] + dist_p[rem->next->id][ins->next->id];
////            int current_dist = saved_dist - dist_p[ins->id][ins->next->id] + dist[ins->id][rem->next->id][ins->next->id];
//            if (current_dist < 0) {
//              Elem *to_be_moved = rem->next;
//              rem->next = to_be_moved->next;
//              to_be_moved->next = ins->next;
//              ins->next = to_be_moved;
//
//              found = true;
//              next = to_be_moved;
//              break;
//            }
//          }
//          rem = rem->next;
//        } while (!found && rem != current);
////      if (!found) {
////        auto tmp = current;
////        do {
////          cout << "id: " << tmp->id << " x: " << vec_points[tmp->id].x << " y: " << vec_points[tmp->id].y << endl;
////          tmp = tmp->next;
////        } while (tmp != current);
////      }
//
//      } while (found);
//    }
//
//    int sum = 0;
//    int last_id = next->id;
//    for (auto current_elem = next->next; current_elem != next;) {
//      Elem* tmp = current_elem;
//      sum += dist_p[last_id][tmp->id];
//      last_id = tmp->id;
//      current_elem = current_elem->next;
//      delete tmp;
//    }
//    sum += dist_p[last_id][next->id];
//    delete next;

		std::cout << sum << '\n';
	}
	return 0;
}
