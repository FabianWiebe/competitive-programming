#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iterator>
#include <utility>
#include <unordered_set>
#include <fstream>


int main (void) {
	std::ios::sync_with_stdio(false);

  	// std::ifstream in("largeSample.in");
   //  // std::streambuf *cinbuf = std::cin.rdbuf(); //save old buf
   //  std::cin.rdbuf(in.rdbuf());

	int total_number;
	std::cin >> total_number;
	std::vector<std::vector<int>> graph;
	std::vector<int> in_counter;
	while (--total_number >= 0) {
		int station_no, connection_no;
		std::cin >> station_no >> connection_no;
		if (connection_no <= 0) {
			continue;
		}
		graph.resize(station_no);
		in_counter.resize(station_no);
		for (auto graph_itr = graph.begin(); graph_itr != graph.end(); ++graph_itr) {
			*graph_itr = std::vector<int>();
		}
		for (int i = 0; i < connection_no; ++i) {
			int start, end;
			std::cin >> start >> end;
			graph.at(start).push_back(end);
			++in_counter[end];
		}
		std::vector<int> no_entries;
		int counter = 0;
		for (auto & entries : in_counter) {
			if (entries == 0) {
				no_entries.push_back(counter);
			}
			++counter;
		}
		while (no_entries.size() > 0) {
			auto val = no_entries.back();
			no_entries.pop_back();
			std::cout << val << std::endl;
			for (auto & vertex : graph[val]) {
				if (--in_counter[vertex] == 0) {
					no_entries.push_back(vertex);
				}
			}

		}

	}
	return 0;
}