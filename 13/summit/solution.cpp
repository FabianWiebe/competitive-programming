#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <fstream>

using namespace std;


int main (void) {
//	std::ios::sync_with_stdio(false);
//  std::cin.tie(NULL);
	std::ifstream ins("sample.in");
	std::cin.rdbuf(ins.rdbuf());
	int nodes_no, edges_no, counter;
	std::cin >> counter;
	while (--counter >= 0) {	
		std::cin >> nodes_no >> edges_no;
		int first, second;
		long weight;
		std::vector<long> distances(nodes_no, 0);
		std::vector<Edge> edges(edges_no);
		// std::vector<std::vector<Pointer>> edges_up(nodes_no);
		// std::vector<std::vector<Pointer>> edges_down(nodes_no);
		auto itr = edges.begin();
		for (int i = 0; i < edges_no; ++i) {
		    std::cin >> first >> second >> weight;
		    // if (first < second) {
		    // 	edges_up[first].emplace_back(second, weight);
		    // } else {
		    // 	edges_down[first].emplace_back(second, weight);
		    // }
		    *itr = Edge{first, second, weight};
		    ++itr;
		}
		// std::vector<int> queue;
		bool no_pos_loop = false;
		// do {
		// 	for (int i = 0; i < nodes_no; ++i) {

		// 	}
		// 	for (int i = nodes_no - 1; i >= 0;--i) {
				
		// 	}
		// } while (!queue.empty());
		for (int k = 0; k <= nodes_no; ++k) {
			for (auto & edge : edges) {
				long sum = distances[edge.first] + edge.weight;
				if(distances[edge.second] < sum) {
					distances[edge.second] = sum;
					if (k == nodes_no) {
						no_pos_loop = true;
						break;
					}
				}
			}
		}
		std::cout << !no_pos_loop << '\n';
	}
	return 0;
}
