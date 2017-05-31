#include <iostream>
#include <cstdint>

int main (void) {
	std::ios::sync_with_stdio(false);
	int total_number;
	std::cin >> total_number;
	while (--total_number >= 0) {
		uint64_t min = 0;
		uint64_t max = UINT64_MAX;
		uint64_t middle = 64;
		bool start = true;
		char in;
		while(max - min > 1) {
			if (start) {
				middle *= 2;
			} else {
				middle = max / 2 + min / 2 + (max % 2 + min % 2) / 2;
			}
			std::cout << "a " << middle  << std::endl;
			std::cin >> in;
			if (start) {
				if (in == 't' || middle >= UINT64_MAX / 2) {
					start = false;
				}
			}
			if (in == 'h') { // hard
				min = middle;
			} else { // too hard
				max = middle;
			}
		}
		if (min == 0 && max == 1) {
			middle = 0;
			std::cout << "a " << middle << std::endl;
			std::cin >> in;
			if (in == 'h') { // hard
				min = middle;
			} else { // too hard
				max = middle;
			}
		}
		std::cout << "i " << max << std::endl;
	}
	return 0;
}
