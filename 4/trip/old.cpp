#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iterator>
#include <utility>
#include <unordered_map>

// template <typename T>
// struct Entry {
// 	Entry(T v, Entry<T> * prev = nullptr, Entry<T> * p = nullptr) : value(std::move(v)),
// 				parent(p), previous(prev), is_root(true) {
// 		if (!parent) {
// 			this->parent = this;
// 		} else {
// 			this->is_root = false;
// 		}
// 	}
// 	T value;
// 	Entry<T> * parent;
// 	Entry<T> * previous;
// 	bool is_root;
// 	Entry<T> * get_representative() {
// 		if (this->is_root) {
// 			return this;
// 		}
// 		return this->parent = this->parent->get_representative();
// 	}
// 	inline bool is_in_same_set(Entry<T> * e) {
// 		return this->get_representative() == e->get_representative();
// 	}
// 	inline bool merge (Entry<T> * e) {
// 		if (this->is_in_same_set(e)) {
// 			return false;
// 		}
// 		this->parent->is_root = false;
// 		e->parent->previous = this->parent->previous;
// 		this->parent->parent = e->parent;
// 		return true;
// 	}
// };

using entry = Entry<int>;

int main (void) {
	std::ios::sync_with_stdio(false);
	int total_number;
	std::cin >> total_number;
	std::vector<entry*> chairs;
	int available_chairs;
	while (--total_number >= 0) {
		// std::cout <<"next try"<< std::endl; 
		int chairs_no, rounds_no;
		std::cin >> chairs_no >> rounds_no;
		if (rounds_no <= 0) {
			continue;
		}
		available_chairs = chairs_no;
		chairs.resize(chairs_no);
		auto chairs_itr = chairs.begin();
		*chairs_itr = new entry(0);
		for (int i = 1; i < chairs_no; ++i) {
			auto prev = *chairs_itr;
			*++chairs_itr = new entry(i, prev);
		}
		chairs.front()->previous = chairs.back();
		for (int i = 0; i < rounds_no; ++i) {
			std::string action;
			int value;
			std::cin >> action >> value;
			if (action.front() == 't')  { // taken
				// std::cout <<"taken "<<action<< std::endl;
				if (chairs.at(value)->is_root && --available_chairs > 0) {
					chairs.at(value)->merge(chairs.at((value + 1) % chairs_no));
				}
			} else { // search
				std::cout << chairs.at(value)->get_representative()->value << std::endl;
			}
		}

		// for (auto & chair : chairs) {
		// 	delete chair;
		// }
	}
	return 0;
}