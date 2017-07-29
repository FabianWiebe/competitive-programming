#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

struct Broom {
    int position;
    int length;
};

vector<Broom> _brooms;

int find_max(int first, int last) {
  vector<Broom> &brooms = _brooms;
  int counter = 0;
  for (int i = first; i <= last; ++i) {

  }
  return counter;
}

int main () {
//	std::ios::sync_with_stdio(false);
//  std::cin.tie(NULL);
	 std::ifstream in("sample.in");
	 std::cin.rdbuf(in.rdbuf());
  vector<Broom> &brooms = _brooms;
	int total_number;
	while (--total_number >= 0) {
	  int broom_no, counter = 0;
    cin >> broom_no;
    brooms.resize(broom_no);
    for (auto itr = brooms.begin(); itr != brooms.end(); ++itr) {
      int position, length;
      cin >> position >> length;
      *itr = {position, length};
    }
    sort(brooms.begin(), brooms.end(), [](const Broom & b1, const Broom & b2) {
       if (b1.position == b2.position) {
         return b1.length < b2.length;
       }
      return b1.position < b2.position;
    });


    cout << find_max(0, broom_no - 1) << '\n';
	}
	return 0;
}