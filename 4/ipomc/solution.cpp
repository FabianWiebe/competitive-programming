#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iterator>
#include <utility>
#include <unordered_map>

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

using entry = Entry<size_t>;

struct Edge
{
	int first;
	int second;
	int weight;
};

int main (void) {
	std::ios::sync_with_stdio(false);
	int total_number;
	std::cin >> total_number;
	int vertices_no, edges_no;
	int first, second, weight;
	std::vector<entry*> graph;
	std::vector<Edge> edges;
	while (--total_number >= 0) {
		std::cin >> vertices_no >> edges_no;
		if (edges_no <= 0) {
			std::cout << 0 << std::endl;
			continue;
		}
		graph.resize(vertices_no);
		auto grapt_itr = graph.begin();
		for (size_t i = 0; i < vertices_no; ++i) {
			*grapt_itr = new entry(i);
			++grapt_itr;
		}

		edges.resize(edges_no);
		auto itr = edges.begin();
		auto itr_end = edges.end();
		while (itr != itr_end) {
			std::cin >> first >> second >> weight;
			*itr = Edge{first, second, weight};
			++itr;
		}
		std::sort(edges.begin(), itr_end, [] (const Edge & l, const Edge & r){
			return l.weight > r.weight;
		});
		unsigned long sum = 0;
		for (auto & edge : edges) {
			if(graph[edge.first]->merge(graph[edge.second])) {
				sum += edge.weight;
			}
		}
		std::cout << sum << std::endl;

		for (auto & v : graph) {
			delete v;
		}
	}
	return 0;
}