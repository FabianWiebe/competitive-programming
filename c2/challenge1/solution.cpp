#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iterator>
#include <utility>
#include <unordered_map>
#include <fstream>
#include <cstdint>

using namespace std;

struct Edge
{
    size_t first;
    size_t second;
    int weight;
};

int main (void) {
  std::ios::sync_with_stdio(false);
  std::cin.tie(NULL);
//  	 std::ifstream in("sample.in");
//	 std::cin.rdbuf(in.rdbuf());
  int total_number;
  std::cin >> total_number;
  size_t first, second, nodes_no, connection_no;
  int weight;
  std::vector<vector<pair<size_t, int >>> al;
  while (--total_number >= 0) {
    cin >> nodes_no >> connection_no;
    al.clear();
    al.resize(nodes_no);

    for (size_t i = 0; i < connection_no; ++i) {
      std::cin >> first >> second >> weight;
      al[first].emplace_back(second, weight);
//      al[second].emplace_back(first, weight);
    }
    Edge current{0u, 0u, INT32_MAX};
    vector<bool> checked(nodes_no, false);
    for (size_t i = 0; i < nodes_no; ++i) {
      if (checked[i] || al[i].empty()) {
        continue;
      }
      checked[i] = true;
      vector<int> dist(nodes_no, INT32_MAX);
      vector<pair<size_t, int>> stack{{i, 0}};
      size_t away = 0;
      while (!stack.empty()) {
        auto val = stack.back();
        stack.pop_back();
        if (dist[val.first] != INT32_MAX && dist[val.first] < val.second) {
          continue;
        }
        dist[val.first] = val.second;
        if (val.second < dist[away]) {
          away = val.first;
        }
        for (auto &p : al[val.first]) {
          if (dist[p.first] == INT32_MAX || dist[p.first] > p.second + val.second) {
            stack.emplace_back(p.first, p.second + val.second);
          }
          checked[p.first] = true;
        }
      }
      if (current.weight == INT32_MAX || dist[away] != INT32_MAX && current.weight > dist[away]) {
        current = Edge{i, away, dist[away]};
      }
//      cout << i << " " << away << " " <<dist[away] << endl;
    }
//    dist.clear();
//    dist.resize(nodes_no, INT32_MAX);
//    stack.clear();
//    stack.emplace_back(away, 0);
//    size_t start = away;
//    while (!stack.empty()) {
//      auto val = stack.back();
//      stack.pop_back();
//      dist[val.first] = val.second;
//      if (val.second > dist[away]) {
//        away = val.first;
//      }
//      for (auto &p : al[val.first]) {
//        if (dist[p.first] == INT32_MAX) {
//          stack.emplace_back(p.first, p.second + val.second);
//        }
//      }
//    }

    std::cout << current.first << ' ';
    std::cout << current.second << ' ';
    std::cout << current.weight*-1 << '\n';
  }
  return 0;
}
