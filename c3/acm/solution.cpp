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
	// std::ios::sync_with_stdio(false);
  // std::cin.tie(NULL);
  ifstream in("sample.in");
  cin.rdbuf(in.rdbuf());
	int total_number;
	cin >> total_number;
	while (--total_number >= 0) {

    cout << " " << '\n';
	}
	return 0;
}