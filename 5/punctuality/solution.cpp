#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iterator>
#include <utility>
#include <unordered_map>
#include <queue>
#include <cassert>
#include <stdexcept>
#include <fstream>
#include <set>

using my_pair_t = std::pair<size_t, long long>;

using my_container_t = std::vector<my_pair_t>;

using Map = std::unordered_map<std::string, size_t>;

inline size_t get_id(Map & translator, const std::string & str) {
  auto find = translator.find(str);
  if (find == translator.end()) {
    size_t new_id = translator.size();
    translator[str] = std::move(new_id);
    return new_id;
  }
  return find->second;
}

using namespace std;

int main (void) {
	std::ios::sync_with_stdio(false);
	int question_no;
	std::cin >> question_no;
	std::string start, end;
  size_t start_id, end_id, first_id, second_id, edges_no;
  long long weight;
  start_id = 0;
	Map translator{{"Gryffindor-Common-Room", start_id}};
	std::vector<std::unordered_map<size_t, long long>> al;
	while (--question_no >= 0) {
		std::cin >> end >> edges_no;
    end_id = get_id(translator, end);
		for (size_t i = 0; i < edges_no; ++i) {
      std::string first, second;
			std::cin >> first >> second >> weight;
      first_id = get_id(translator, first);
      second_id = get_id(translator, second);

      al.resize(translator.size());
      if (weight == 0) {
        auto find = al[first_id].find(second_id);
        if (find != al[first_id].end()) {
          al[first_id].erase(find);
          al[second_id].erase(al[second_id].find(first_id));
        }
      } else {
        al[first_id][second_id] = weight;
        al[second_id][first_id] = weight;
      }
		}

		size_t nodes_no = translator.size();

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
          long long sum = current.second + connection.second;
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
    std::cout << queue.top().second << '\n';
    start_id = end_id;
	}
	return 0;
}
