#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iterator>

int main (void) {
	std::ios::sync_with_stdio(false);
	int total_number;
	int iterations = 0;
	std::cin >> total_number;
	std::string line;
	while (++iterations <= total_number && std::cin >> line) {
		const size_t length = line.length();
		if (length < 2) {
			std::cout << -1 << std::endl;
			continue;
		}

		const bool odd = length & 1;

		const auto line_begin = line.begin();
		const auto line_end = line.end();
		const auto before_end = line_end - 1;

		size_t counter = 0;
		bool current_single_middle = odd;
		bool current_up = true;
		bool current_single_middle_up = current_single_middle;
		bool current_single_middle_down = !current_single_middle;
		auto up_itr = line_begin + length / 2;
		auto down_itr = up_itr - 1;

		auto tmp_up_itr = up_itr;
		auto tmp_down_itr = down_itr;


		size_t tmp_loop_counter = 0;
		while (up_itr != line_end) {
			size_t tmp_counter = 1;
			current_up = !current_up;
			if (tmp_loop_counter + counter >= length) {
				break;
			}
			if (current_up == odd) { 
				++tmp_loop_counter;
			}
			if (!current_up) {
				current_single_middle_up = !current_single_middle_up;
				if (!current_single_middle_up) {
					tmp_down_itr = up_itr;
					tmp_up_itr = up_itr;
					++up_itr;
				} else {
					tmp_down_itr = up_itr - 1;
					tmp_up_itr = up_itr;
					if (*tmp_down_itr == *tmp_up_itr) {
						tmp_counter = 2;
					} else {
						continue;
					}
				}
			} else {
				current_single_middle_down = !current_single_middle_down;
				if (!current_single_middle_down) {
					tmp_down_itr = down_itr;
					tmp_up_itr = down_itr;
					--down_itr;
				} else {
					tmp_down_itr = down_itr;
					tmp_up_itr = down_itr + 1;
					if (*tmp_down_itr == *tmp_up_itr) {
						tmp_counter = 2;
					} else {
						continue;
					}
				}
			}

			while (tmp_down_itr != line_begin && tmp_up_itr != before_end && *--tmp_down_itr == *++tmp_up_itr) {
				tmp_counter += 2;
			}
			if (tmp_counter > counter) {
				counter = tmp_counter;
			}
		}
		if (counter > 1) {
			std::cout << counter << std::endl;
		} else {
			std::cout << -1 << std::endl;
		}
	}

	return 0;
}