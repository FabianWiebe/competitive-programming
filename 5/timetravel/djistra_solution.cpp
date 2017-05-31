#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iterator>
#include <utility>
#include <map>
#include <queue>
#include <cassert>

#include <fstream>

template <typename T>
struct Entry {
	Entry(T v, Entry<T> * p = nullptr) : value(std::move(v)), nodes(1u), parent(p), is_root(true) {
		if (!parent) {
			this->parent = this;
		} else {
			++(this->parent->nodes);
			this->is_root = false;
		}
	}
	T value;
	size_t nodes;
	Entry<T> * parent;
	bool is_root;
	Entry<T> * get_representative() {
		if (this->is_root) {
			return this;
		}
		return this->parent = this->parent->get_representative();
	}
	inline bool is_in_same_set(Entry<T> * e) {
		return this->get_representative() == e->get_representative();
	}
	inline bool merge (Entry<T> * e) {
		if (this->is_in_same_set(e)) {
			return false;
		}
		if (e->nodes > this->nodes) {
			this->parent->is_root = false;
			this->parent->parent = e->parent;
		} else {
			e->parent->is_root = false;
			e->parent->parent = this->parent;
		}
		return true;
	}
	inline Entry<T>* merge_new (T value) {
		return new Entry<T>(value, this);
	}
};

using entry = Entry<int>;
struct Edge
{
	int first;
	int second;
	int weight;
};

using my_pair_t = std::pair<int,long>;
 
using my_container_t = std::vector<my_pair_t>;

int main (void) {
//	 std::ifstream in("sample.in");
//    // std::streambuf *cinbuf = std::cin.rdbuf(); //save old buf
//    std::cin.rdbuf(in.rdbuf());
	std::ios::sync_with_stdio(false);
	int nodes_no, edges_no, question_no;
	std::cin >> nodes_no >> edges_no >> question_no;
//	std::vector<entry*> nodes(nodes_no);
//	auto nodes_itr = nodes.begin();
//	for (int i = 0; i < nodes_no; ++i) {
//		*nodes_itr = new entry(i);
//		++nodes_itr;
//	}
//	std::vector<Edge> edges(edges_no);
	int first, second, weight;
//	auto edges_itr = edges.begin();
//	for (int i = 0; i < edges_no; ++i) {
//		std::cin >> first >> second >> weight;
//		nodes[first]->merge(nodes[second]);
//		*edges_itr = Edge{first, second, weight};
//		++edges_itr;
//	}
	// std::map<int, std::vector<Edge>> graphs;
	// for (auto & edge : edges) {
	// 	auto rep = nodes[edge.first]->get_representative()->value;
	// 	auto search = graphs.find(rep);
	// 	if (search == graphs.end()) {
	// 		graphs[rep] = {edge};
	// 	} else {
	// 		search->second.push_back(edge);
	// 	}
	// }
	std::vector<std::vector<std::pair<int, int>>> al(nodes_no, std::vector<std::pair<int, int>>());
  for (int i = 0; i < edges_no; ++i) {
    std::cin >> first >> second >> weight;
		al[first].emplace_back(second, weight);
	}
    auto my_comp =
        [](const my_pair_t& e1, const my_pair_t& e2) 
        { return e1.second > e2.second; };
    std::priority_queue<my_pair_t,
                        my_container_t,
                        decltype(my_comp)> queue(my_comp);
	std::vector<std::vector<long>> distances(nodes_no, std::vector<long>(nodes_no));
	std::vector<std::vector<bool>> distances_calculated(nodes_no, std::vector<bool>(nodes_no, false));
	std::vector<bool> calculated(nodes_no, false);
	for (int i = 0; i < question_no; ++i) {
		std::cin >> first >> second;
		if (!calculated[first]) {
      // Djistra
			std::priority_queue<my_pair_t,
                        my_container_t,
                        decltype(my_comp)> queue(my_comp);
			std::vector<long> tmp(nodes_no);
			std::vector<bool> tmp_used(nodes_no, false);
			tmp[first] = 0;
			tmp_used[first] = true;
			queue.emplace(first, 0);
			while (!queue.empty()) {
				auto current = queue.top();
				queue.pop();
				distances[first][current.first] = current.second;
				distances_calculated[first][current.first] = true;
				for (auto & connection : al[current.first]) {
					if(!distances_calculated[first][connection.first]) {
						if (!tmp_used[connection.first] || tmp[connection.first] > current.second + connection.second) {
							tmp[connection.first] = current.second + connection.second;
							tmp_used[connection.first] = true;
							queue.emplace(connection.first, current.second + connection.second);
						}
					}
				}
				while(!queue.empty() && distances_calculated[first][queue.top().first]) {
					queue.pop();
				}
			}
			calculated[first] = true;
		}
		if (!distances_calculated[first][second]) {
			std::cout << "oo" << std::endl;
		} else {
			std::cout << distances[first][second] << std::endl;
		}

	}
//	for (auto dist = distances.begin(); dist != distances.end(); ++dist) {
//		for (auto val = dist->begin(); val != dist->end(); ++val) {
//			std::cout << *val << " ";
//		}
//		std::cout << std::endl;
//	}







//	for (auto & node : nodes) {
//		delete node;
//	}
	return 0;
}
