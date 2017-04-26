#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

int main (void) {
	std::ios::sync_with_stdio(false);
	size_t total_number;
	size_t iterations = 0;
	std::cin >> total_number;
	std::string line;
	while (++iterations <= total_number && std::cin >> line) {
		const size_t length = line.length();
		if (length == 1) {
			std::cout << -1 << std::endl;
			continue;
		} else if (length == 0) {
			std::cout << 0 << std::endl;
			continue;
		}
		const bool odd = length & 1;
		// std::vector<char> word (line.begin(), line.end());
		size_t counter = 0;
		auto down_itr = line.begin() + (length - 1) / 2;
		auto up_itr = down_itr + 1;
		auto tmp_up_itr = up_itr;
		auto tmp_down_itr = down_itr;
		bool current_up = false;
		size_t tmp_loop_counter = 0;
		size_t tmp_length = odd ? length : length ^ 1;
		while (down_itr != line.begin() && counter < tmp_length - 2 * tmp_loop_counter) {
			size_t tmp_counter = 1;
			if (current_up) {
				tmp_up_itr = up_itr;
				tmp_down_itr = up_itr;
				++up_itr;
			} else {
				tmp_up_itr = down_itr;
				tmp_down_itr = down_itr;
				--down_itr;
			}
			if (current_up != odd) {
				++tmp_loop_counter;
			}
			current_up = !current_up;
			while (*--tmp_down_itr == *++tmp_up_itr) {
				if (tmp_up_itr == line.end()) {
					break;
				}
				tmp_counter += 2;
			}
			if (tmp_counter > counter) {
				counter = tmp_counter;
			}
		}
		down_itr = line.begin() + (length - 1) / 2;
		up_itr = down_itr;
		current_up = true;
		// std::cout << line << std::endl;
		auto line_last = --line.end();
		while(down_itr != line.begin() || (!odd && (up_itr != line_last))) {
			size_t tmp_counter = 0;
			// std::cout << "up_itr: " << *up_itr << "  down_itr: " << *down_itr << "   current_up " << current_up << std::endl;
			if (current_up) {
				tmp_down_itr = up_itr;
				++up_itr;
				tmp_up_itr = up_itr;
			} else {
				tmp_up_itr = down_itr;
				--down_itr;
				tmp_down_itr = down_itr;
			}
			// std::cout << "up_itr: " << *up_itr << "  down_itr: " << *down_itr  << std::endl;
			current_up = !current_up;
			while (*tmp_down_itr == *tmp_up_itr) {
				--tmp_down_itr;
				++tmp_up_itr;
				tmp_counter += 2;
				if (tmp_up_itr == line.end()) {
					break;
				}
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