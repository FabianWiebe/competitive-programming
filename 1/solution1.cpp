#include <iostream>
#include <array>
#include <map>
#include <string>
#include <vector>

using namespace std;

constexpr int offset = 'a';

int main (void) {
	ios::sync_with_stdio(false);
	std::string a;
	std::string b;
	int number;
	int counter = 0;
	cin >> number;
	std::map<char, int> m;
	auto end = m.end();
	while (++counter <= number && std::cin >> a && std::cin >> b) {
		bool result = true;
		for(auto & c : a) {
			auto it = m.find(c);
			if (it == end) {
				m[c] = 1;
			} else {
				++(it->second);
			}
		}
		for(auto & c : b) {
		    auto it = m.find(c);
			if (it == end) {
				result = false;
				break;
			} else {
				--(it->second);
			}
		}
		for (auto & elem : m) {
			if (elem.second != 0) {
				result = false;
				elem.second = 0;
			}
		}
		std::cout << result << std::endl;
	}

	return 0;
}