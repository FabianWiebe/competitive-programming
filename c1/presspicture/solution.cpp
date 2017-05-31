#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iterator>
#include <utility>
#include <unordered_map>
#include <chrono>
#include <thread>

#include <fstream>

using namespace std;
using mapping = pair<char, int>;

int main (void) {
	std::ios::sync_with_stdio(false);
	// std::cin.tie(NULL);
//	    std::ifstream ins("sample.in");
//      std::cin.rdbuf(ins.rdbuf());
	int total_number;
	string number_s;
	std::getline(std::cin, number_s);
	total_number = stoi(number_s);
	string in;
	while (--total_number >= 0) {		
		std::getline(std::cin, in);
		int length = in.length();
		if (length == 0) {
			cout << '\n';
			continue;
		}

		vector<mapping> count(26);
		for (int i = 0; i < 26; ++i) {
			count[i] = make_pair('a' + i, 0);
		}
		for (char c : in) {
			++(count[c - 'a'].second);
		}

		sort(count.begin(), count.end(), [](mapping & m1, mapping & m2) {
			return m1.second > m2.second;
		});
		int tmp_length = length & 1 ? length + 1 : length;

		if (count[0].second * 2 > tmp_length) {
			cout << '#' << '\n';
			continue;
		}
		vector<int> next(27, -2);
		vector<int> prev(27, -2);
		int pos = 0;
		for (int i = 0; i < 26; ++i) {
      	if (count[i].second == 0) {
	        next.resize(i+1);
	        prev.resize(i+1);
	        next[pos] = i;
	        prev[i] = pos;
	        break;
      	}
			if (count[pos].second != count[i].second) {
				next[pos] = i;
				prev[i] = pos;
				pos = i;
			}
		}
		int current_id = next[0]-1;
		while (--length >= 0) {
			cout << count[current_id].first;
			--(count[current_id].second);

			if (current_id == 0) {
				if (count[0].second == count[1].second) {
					next[0] = next[1];
					prev[next[1]] = current_id;
				}
			} else if (current_id == 25) {
		        prev[current_id] = prev[current_id+1];
		        next[prev[current_id+1]] = current_id;
		    } else {
				if (count[current_id -1].second - 1 == count[current_id].second) {
					next[prev[current_id+1]] = current_id;
					prev[current_id] = prev[current_id+1];
          			next[current_id] = current_id + 1;
				}
				if (count[current_id].second == count[current_id+1].second) {
					next[current_id] = next[current_id+1];
					prev[next[current_id+1]] = current_id;
				} else {
	          		prev[current_id+1] = current_id;
	        	}
			}
			if (current_id == next[0]-1) {
        		current_id = next[1]-1;
			} else {
				current_id = next[0]-1;
			}

		}
		cout << '\n';

	}
	return 0;
}