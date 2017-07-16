#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <fstream>
#include <algorithm>
#include <stdexcept>

using namespace std;

struct Point {
    Point(int x_, int y_, int id_) : x(x_), y(y_), id(id_) {}
    int x;
    int y;
    int id;
};

constexpr int max_size = 50; // 50
int grid_neighbors[max_size][max_size];
int grid[max_size][max_size];
int direction[max_size][max_size];
bool visited[max_size][max_size];
int street_no, avenue_no, crossing_no;

void reduce_neighbor_counts(const int x, const int y) {
  if (x > 0) {
    --grid_neighbors[x-1][y];
  }
  if (x < street_no-1) {
    --grid_neighbors[x+1][y];
  }
  if (y > 0) {
    --grid_neighbors[x][y-1];
  }
  if (y < avenue_no-1) {
    --grid_neighbors[x][y+1];
  }
}



bool find_route(int x, int y, int dir = 0) {
  int (&_grid_neighbors)[max_size][max_size] = grid_neighbors;
  int (&_grid)[max_size][max_size] = grid;
  int (&_direction)[max_size][max_size] = direction;
  if (visited[x][y]) {
    return false;
  }
  visited[x][y] = true;
  if (grid[x][y] > 0 || (grid[x][y] < 0 && direction[x][y] != dir)) {
    return false;
  }
  if (x == 0) {
    direction[x][y] = 4;
    return true;
  } else if (x == street_no - 1) {
    direction[x][y] = 2;
    return true;
  } else if (y == 0) {
    direction[x][y] = 3;
    return true;
  } else if (y == avenue_no - 1) {
    direction[x][y] = 1;
    return true;
  }

  if (direction[x][y] != 0 && direction[x][y] != dir) {
    if (direction[x][y-1] == 1) {
      return find_route(x, y-1, 1);
    } else if (direction[x-1][y] == 2) {
      return find_route(x-1, y, 2);
    } else if (direction[x][y+1] == 3) {
      return find_route(x, y+1, 3);
    } else if (direction[x+1][y] == 4) {
      return find_route(x+1, y, 4);
    } else {
      throw std::runtime_error("error");
    }
  }
  if (x == 24 && y == 24) {
    cout << flush;
  }

  int above = direction[x][y+1];
  int right = direction[x+1][y];
  int below = direction[x][y-1];
  int left = direction[x-1][y];
  if (direction[x][y] != 1 && find_route(x, y+1, 3)) {
  // up 1
    if (direction[x][y] == 0) {
      direction[x][y] = 1;
    } else if (direction[x][y] == dir) {
      if (above == 3) {
        direction[x][y] = 0;
      } else {
        direction[x][y] = 1;
      }
    }
    return true;
  } else if (direction[x][y] != 2 && find_route(x+1, y, 4)) {
  // right 2
    if (direction[x][y] == 0) {
      direction[x][y] = 2;
    } else if (direction[x][y] == dir) {
      if (right == 4) {
        direction[x][y] = 0;
      } else {
        direction[x][y] = 2;
      }
    }
    return true;
  } else if (direction[x][y] != 3 && find_route(x, y-1, 1)) {
  // down 3
    if (direction[x][y] == 0) {
      direction[x][y] = 3;
    } else if (direction[x][y] == dir){
      if (below == 1) {
        direction[x][y] = 0;
      } else {
        direction[x][y] = 3;
      }
    }
    return true;
  } else if (direction[x][y] != 4 && find_route(x-1, y, 2)) {
  // left 4
    if (direction[x][y] == 0) {
      direction[x][y] = 4;
    } else if (direction[x][y] == dir){
      if (left == 2) {
        direction[x][y] = 0;
      } else {
        direction[x][y] = 4;
      }
    }
    return true;
  }
  return false;
}

int main (void) {
  int (&_grid_neighbors)[max_size][max_size] = grid_neighbors;
  int (&_grid)[max_size][max_size] = grid;
  int (&_direction)[max_size][max_size] = direction;
	std::ios::sync_with_stdio(false);
  std::cin.tie(NULL);
//	std::ifstream ins("largeSample.in");
//	std::cin.rdbuf(ins.rdbuf());
	int counter;
	std::cin >> counter;
  vector<Point> crossings;
  crossings.reserve(500);
  vector<Point> open_crossings;
  open_crossings.reserve(500);
	while (--counter >= 0) {
		std::cin >> street_no >> avenue_no >> crossing_no;
    for (int i = 0; i < street_no; ++i) {
      for (int j = 0; j < avenue_no; ++j) {
        if (i % (street_no - 1) == 0 && j % (avenue_no - 1) == 0) {
          grid_neighbors[i][j] = 2;
        } else if (i % (street_no - 1) == 0 || j % (avenue_no - 1) == 0) {
          grid_neighbors[i][j] = 3;
        } else {
          grid_neighbors[i][j] = 4;
        }
        grid[i][j] = 0;
        direction[i][j] = 0;
      }
    }
    crossings.clear();
    open_crossings.clear();
    for (int i = 1; i <= crossing_no; ++i) {
      int x, y;
      cin >> x >> y;
      --x;
      --y;
      grid[x][y] = i;
      reduce_neighbor_counts(x, y);
      if (x % (street_no - 1) == 0 || y % (avenue_no - 1) == 0) {
        continue;
      }
      crossings.emplace_back(x, y, i);
    }
    if (street_no < 3 || avenue_no < 3) {
      std::cout << "possible" << '\n';
      continue;
    }
    bool possible = true;
//    for (auto point : crossings) {
//      int x = point.x;
//      int y = point.y;
//      if (grid_neighbors[x][y] == 0) {
//        possible = false;
//        break;
//      }
//      if (x == 1) {
//        if (grid[0][y] == 0) {
//          grid[0][y] = point.id;
//          reduce_neighbor_counts(0, y);
//          continue;
//        }
//      }
//      if (x == street_no - 2) {
//        if (grid[street_no - 1][y] == 0) {
//          grid[street_no - 1][y] = point.id;
//          reduce_neighbor_counts(street_no - 1, y);
//          continue;
//        }
//      }
//      if (y == 1) {
//        if (grid[x][0] == 0) {
//          grid[x][0] = point.id;
//          reduce_neighbor_counts(x, 0);
//          continue;
//        }
//      }
//      if (y == avenue_no - 2) {
//        if (grid[x][avenue_no - 1] == 0) {
//          grid[x][avenue_no - 1] = point.id;
//          reduce_neighbor_counts(x, avenue_no - 1);
//          continue;
//        }
//      }
//      open_crossings.push_back(point);
//    }
//    crossings.clear();
//    if (possible) {
//      bool changed = true;
//      while (possible && changed) {
//        crossings = open_crossings;
//        open_crossings = vector<Point>();
//        changed = false;
//        for (auto point : crossings) {
//          int x = point.x;
//          int y = point.y;
//          if (grid_neighbors[x][y] == 0) {
//            possible = false;
//            break;
//          }
//          if (grid_neighbors[x][y] == 1) {
//            changed = true;
//            if (grid[x-1][y] == 0) {
//              grid[x-1][y] = point.id;
//              open_crossings.emplace_back(x-1, y, point.id);
//            } else if (grid[x+1][y] == 0) {
//              grid[x+1][y] = point.id;
//              open_crossings.emplace_back(x+1, y, point.id);
//            } else if (grid[x][y-1] == 0) {
//              grid[x][y-1] = point.id;
//              open_crossings.emplace_back(x, y-1, point.id);
//            } else if (grid[x][y+1] == 0) {
//              grid[x][y+1] = point.id;
//              open_crossings.emplace_back(x, y+1, point.id);
//            }
//          } else {
//            open_crossings.push_back(point);
//          }
//        }
//      }
//    }
    open_crossings = crossings;
    if (possible) {
      sort(open_crossings.begin(), open_crossings.end(), [] (const Point & p1, const Point & p2) {
        int c1 = (p1.x % (street_no/2)) + (p1.y % (avenue_no/2));
        int c2 = (p2.x % (street_no/2)) + (p2.y % (avenue_no/2));
        return c1 > c2;
      });
      for (auto point : open_crossings) {
        grid[point.x][point.y] *= -1;
      }
      for (auto point : open_crossings) {

        for (int j = avenue_no - 1; j >= 0; --j) {
//          cout.width(3);
//          cout << j << " ";
          for (int i = 0; i < street_no; ++i) {
            visited[i][j] = false;
//            cout.width(3);
//            cout << grid[i][j] << " ";
          }
//          cout << std::endl;
        }
//        cout.width(3);
//        cout << -1 << " ";
//        for (int i = 0; i < street_no; ++i) {
//          cout.width(3);
//          cout << i << " ";
//        }
//        cout << endl;
//        cout << endl;

        possible = find_route(point.x, point.y);

//        for (int j = avenue_no - 1; j >= 0; --j) {
//          cout.width(3);
//          cout << j << " ";
//          for (int i = 0; i < street_no; ++i) {
//            cout.width(3);
//            cout << direction[i][j] << " ";
//          }
//          cout << endl;
//        }
//        cout.width(3);
//        cout << -1 << " ";
//        for (int i = 0; i < street_no; ++i) {
//          cout.width(3);
//          cout << i << " ";
//        }
//        cout << endl;
//        cout << endl;

        if (!possible) {
          break;
        }
      }
    }

		std::cout << (possible ? "" : "not ") << "possible" << '\n';
	}
	return 0;
}
