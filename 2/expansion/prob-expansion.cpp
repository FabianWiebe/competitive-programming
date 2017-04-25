#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

using duration = pair<size_t, size_t>;

int main (void) {
	ios::sync_with_stdio(false);
	int total_number;
	cin >> total_number;
	int counter = 0;
	int cur_number = 0;
	size_t start;
	size_t end;
	while (++counter <= total_number && cin >> cur_number) {
		vector<duration> times(cur_number);
		auto itr = times.begin();
		do {
			cin >> start;
			cin >> end;
			*itr = make_pair(start, end);
		} while (++itr != times.end());
		sort(times.begin(), times.end(), [](duration a, duration b) {
	        return a.second < b.second;   
	    });
	    // for (auto & pair : times) {
	    // 	cout << pair.first << " " << pair.second << endl;
	    // }
	    size_t counter = 0;
	    for (int offset = 0; offset < cur_number - 1; ++offset) {
	    	size_t tmp_counter = 0;
		    for (int i = offset; i < cur_number; ++i) {
		    	if (times[i].first < times[offset].second) {
		    		++tmp_counter;
		    	}
		    }
		    if (tmp_counter > counter) {
		    	counter = tmp_counter;
		    }
		}
		cout << counter << endl;
	}

	return 0;
}