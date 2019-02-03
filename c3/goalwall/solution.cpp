#include <iostream>
#include <vector>
#include <fstream>
#include <utility>
#include <algorithm>
#include <iomanip>
#include <limits>
#include <cmath>

using namespace std;

int main (void) {
	 std::ios::sync_with_stdio(false);
   std::cin.tie(NULL);
//  ifstream in("largeSample.in");
//  cin.rdbuf(in.rdbuf());
	int total_number;
	cin >> total_number;
	vector<int> holes;
	while (--total_number >= 0) {
		int h, tests_no;
		cin >> h >> tests_no;
		holes.clear();
		holes.reserve(h);
		for (size_t i = 0; i < h; ++i) {
			int tmp;
			cin >> tmp;
			holes.push_back(tmp);
		}
		sort(holes.begin(), holes.end(), [](int a, int b) {return a > b;});

//		int tests_no;
//		cin >> tests_no;

		int end = 1;
		vector<int> counter;
		counter.push_back(0);

		for (size_t i = 0; i < tests_no; ++i) {
			int question;
			cin >> question;
			if (end <= question) {
				for (size_t current_check = end; current_check <= question; ++current_check) {
					int current = -1;
					for (auto hole : holes) {
            if (hole == current_check) {
              current = 1;
              break;
            }
						if (hole <= current_check) {
							if (counter.at(current_check - hole) != -1) {
								int tmp = counter[current_check - hole] + 1;
                if (current == -1 || tmp < current) {
                  current = tmp;
                }
							}
						}
					}
					counter.push_back(current);
				}
				end = question + 1;
			}
			if (counter[question] == -1) {
				cout << "not possible" << '\n';
			} else {
        int tmp = counter[question];
	    	cout << counter[question] << '\n';
			}
		}


	}
	return 0;
}