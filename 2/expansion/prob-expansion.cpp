#include <iostream>
#include <vector>
#include <algorithm>

int main (void) {
	std::ios::sync_with_stdio(false);
	int total_number;
	std::cin >> total_number;
	int iterations = 0;
	int cur_number = 0;
	while (++iterations <= total_number && std::cin >> cur_number) {
		if (cur_number == 0) {
			std::cout << 0 << std::endl;
			continue;
		}
		std::vector<size_t> start_times(cur_number);
		std::vector<size_t> end_times(cur_number);
		auto start_itr = start_times.begin();
		auto end_itr = end_times.begin();
		while (start_itr != start_times.end()) {
			std::cin >> *start_itr;
			std::cin >> *end_itr;
			++start_itr;
			++end_itr;
		}
		std::sort(start_times.begin(), start_times.end());
		std::sort(end_times.begin(), end_times.end());
		size_t counter = 0;
		size_t tmp_counter = 0;
		start_itr = start_times.begin();
		end_itr = end_times.begin();
		while (start_itr != start_times.end()) {
			if (*start_itr < *end_itr) {
				++start_itr;
				++tmp_counter;
		    	if (tmp_counter > counter) {
		    		counter = tmp_counter;
		    	}
			} else {
				++end_itr;
				--tmp_counter;
			}
		}
		std::cout << counter << std::endl;
	}

	return 0;
}