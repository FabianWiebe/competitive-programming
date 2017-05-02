#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iterator>
#include <utility>

using vote = std::pair<size_t, size_t>;

int main (void) {
	std::ios::sync_with_stdio(false);
	int total_number;
	int iterations = 0;
	std::cin >> total_number;
	int current_number;
	size_t first, second;
	while (++iterations <= total_number && std::cin >> current_number) {
		if (current_number <= 0) {
			std::cout << 0 << std::endl;
			continue;
		}

		std::vector<vote> times(current_number);
		auto itr = times.begin();
		auto itr_end = times.end(); 
		while(itr != itr_end) {
			std::cin >> first >> second;
			*itr = std::make_pair(first, second);
			++itr;
		}
		std::sort(times.begin(), itr_end,[](vote a, vote b) {
			return a.second > b.second;
		});

		unsigned long total_time = 0;
		unsigned long current_time = 0;
		for (auto &time : times) {
			current_time += time.first;
			if (current_time + time.second > total_time) {
				total_time = current_time + time.second;
			}
		}

		std::cout << total_time << std::endl;
	}

	return 0;
}