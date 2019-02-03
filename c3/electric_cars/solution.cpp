#include <iostream>
#include <vector>
#include <fstream>
#include <utility>
#include <algorithm>
#include <iomanip>
#include <limits>
#include <queue>
#include <cmath>


using namespace std;

using my_pair_t = std::pair<int, int>;

using Edge = pair<int, int>;

using my_container_t = std::vector<my_pair_t>;

int main (void) {
	 std::ios::sync_with_stdio(false);
   std::cin.tie(NULL);
//  ifstream in("sample.in");
//  cin.rdbuf(in.rdbuf());
	int total_number;
	cin >> total_number;
	while (--total_number >= 0) {
    int nodes_no, edges, start_id, end_id;
    cin >> nodes_no >> edges >> start_id >> end_id;
    vector<vector<Edge>> al(edges);
    for (size_t i = 0; i < edges; ++i) {
      int start, end, dist;
      cin >> start >> end >> dist;
      al[start].emplace_back(end, dist);
      al[end].emplace_back(start, dist);
    }


    // start dijkstra
    std::vector<long long> distances(nodes_no, -1);

    auto my_comp =
            [](const my_pair_t& e1, const my_pair_t& e2)
            { return e1.second >= e2.second; };
    std::priority_queue<my_pair_t,
            my_container_t,
            decltype(my_comp)> queue(my_comp);
    std::vector<long long> tmp(nodes_no, -1);
    tmp[start_id] = 0;
    queue.emplace(start_id, 0);

    while (queue.top().first != end_id) {
      auto current = queue.top();
      queue.pop();
      distances[current.first] = current.second;
      for (auto & connection : al[current.first]) {
        if(distances[connection.first] == -1) {
          long long sum = max(current.second, connection.second);
          if (tmp[connection.first] == -1 || tmp[connection.first] > sum) {
            tmp[connection.first] = sum;
            queue.emplace(connection.first, sum);
          }
        }
      }
      while(!queue.empty() && distances[queue.top().first] != -1) {
        queue.pop();
      }
    }
    cout << queue.top().second << '\n';
	}
	return 0;
}