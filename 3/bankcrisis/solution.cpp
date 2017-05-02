#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iterator>
#include <utility>
#include <map>

struct Entry {
	Entry(size_t value, Entry * parent) : value(value), parent(parent) {}
	size_t value;
	Entry * parent;
	inline bool is_root() {
		return this == parent;
	}
	Entry * get_representative() {
		if (this->is_root()) {
			return this;
		}
		return this->parent = this->parent->get_representative();
	}
	inline bool is_in_same_set(Entry * e) {
		return this->get_representative() == e->get_representative();
	}
};

using connection = std::pair<size_t, size_t>;

int main (void) {
	std::ios::sync_with_stdio(false);
	int total_number;
	std::cin >> total_number;
	if (total_number <= 0) {
		return 0;
	}
	size_t first, second;
	std::vector<connection> graph(total_number);
	auto itr = graph.begin();
	auto itr_end = graph.end(); 
	while(itr != itr_end) {
		std::cin >> first >> second;
		*itr = std::make_pair(first, second);
		++itr;
	}

	std::map<size_t, Entry*> sets;

	for (auto & conn : graph) {
		auto find_first = sets.find(conn.first);
		auto find_second = sets.find(conn.second);
		auto sets_end = sets.end();
		if (find_first == sets_end && find_second == sets_end) {
			auto entry_ptr = new Entry(conn.first, nullptr);
			entry_ptr->parent = entry_ptr;
			sets[conn.first] = entry_ptr;
			sets[conn.second] = new Entry(conn.second, entry_ptr);
		} else if (find_first == sets_end) {
			sets[conn.first] = new Entry(conn.first, find_second->second);
		} else if (find_second == sets_end) {
			sets[conn.second] = new Entry(conn.second, find_first->second);
		} else {
			if (!find_first->second->is_in_same_set(find_second->second)) {
				find_second->second->parent->parent = find_first->second;
			}
		}
	}

	std::map<size_t, std::vector<size_t>> result;

	for (auto & e : sets) {
		size_t value = e.second->get_representative()->value;
		auto res_find = result.find(value);
		if (res_find == result.end()) {
			result[value] = {e.first};
		} else {
			result[value].push_back(e.first);
		}
	}

	std::vector<std::vector<size_t>> final_result(result.size());
	auto res_itr = final_result.begin();
	for (auto & r : result) {
		*res_itr = r.second;
		std::sort(res_itr->begin(), res_itr->end());
		++res_itr;
	}
	std::sort(final_result.begin(), final_result.end(), [](std::vector<size_t> & a, std::vector<size_t> & b) {
		return a[0] < b[0];
	});
	for (auto & r : final_result) {
		std::copy(r.begin(), --r.end(), std::ostream_iterator<size_t>(std::cout, ", "));
		std::cout << *--r.end() << std::endl;
	}

	return 0;
}