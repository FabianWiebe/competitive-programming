#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iterator>
#include <utility>
#include <unordered_map>

int getNextFree(std::vector<int> & list, int pos) {
	if (list[pos] == pos) {
		return pos;
	}
	return list[pos] = getNextFree(list, list[pos]);
}

int main (void) {
	std::ios::sync_with_stdio(false);
	int total_number;
	std::cin >> total_number;
	std::vector<int> chairs;
	int available_chairs;
	while (--total_number >= 0) {
		int chairs_no, rounds_no;
		std::cin >> chairs_no >> rounds_no;
		if (rounds_no <= 0) {
			continue;
		}
		available_chairs = chairs_no;
		chairs.resize(chairs_no);
		auto chairs_itr = chairs.begin();
		for (int i = 0; i < chairs_no; ++i) {
			*chairs_itr++ = i;
		}
		for (int i = 0; i < rounds_no; ++i) {
			std::string action;
			int value;
			std::cin >> action >> value;
			if (action.front() == 't')  { // taken
				if (chairs[value] == value && --available_chairs > 0) {
					chairs[value] = (value + 1) % chairs_no;
				}
			} else { // search
				std::cout << getNextFree(chairs, value) << std::endl;
			}
		}
	}
	return 0;
}