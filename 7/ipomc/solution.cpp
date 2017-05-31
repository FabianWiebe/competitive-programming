#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iterator>
#include <utility>
#include <unordered_map>
#include <fstream>

using namespace std;

struct Edge
{
	size_t first;
	size_t second;
	size_t weight;
};

int main (void) {
	std::ios::sync_with_stdio(false);
  std::cin.tie(NULL);
	size_t total_number;
	std::cin >> total_number;
	size_t first, second, weight;
	std::vector<vector<pair<size_t, long long >>> al(total_number);

  for (size_t i = 1; i < total_number; ++i) {
    std::cin >> first >> second >> weight;
    al[first].emplace_back(second, weight);
    al[second].emplace_back(first, weight);
  }
  vector<long long> dist(total_number, -1);
  vector<pair<size_t, long long>> stack{{0, 0}};
  size_t away = 0;
  while(!stack.empty()){
    auto val = stack.back();
    stack.pop_back();
    dist[val.first] = val.second;
    if (val.second > dist[away]) {
      away = val.first;
    }
    for (auto & p : al[val.first]) {
      if (dist[p.first] == -1) {
        stack.emplace_back(p.first, p.second + val.second);
      }
    }
  }

  dist.clear();
  dist.resize(total_number, -1);
  stack.clear();
  stack.emplace_back(away, 0);
  size_t start = away;
  while(!stack.empty()){
    auto val = stack.back();
    stack.pop_back();
    dist[val.first] = val.second;
    if (val.second > dist[away]) {
      away = val.first;
    }
    for (auto & p : al[val.first]) {
      if (dist[p.first] == -1) {
        stack.emplace_back(p.first, p.second + val.second);
      }
    }
  }

  std::cout << dist[away] << '\n';
  std::cout << std::min(start, away) << '\n';
  std::cout << std::max(start, away) << '\n';
	return 0;
}
