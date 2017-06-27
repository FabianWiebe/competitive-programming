#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

int main (void) {
	std::ios::sync_with_stdio(false);
  std::cin.tie(NULL);
//	 std::ifstream in("largeSample.in");
//	 std::cin.rdbuf(in.rdbuf());
	int total_number;
  vector<unsigned long> prices;
	std::cin >> total_number;
  vector<size_t > inserted;
	while (--total_number >= 0) {
    size_t total_length;
    int price_count;
		std::cin >> total_length >> price_count;
    prices.clear();
    prices.resize(total_length + 1, 0);
    inserted.clear();
    while (--price_count >= 0) {
      size_t number;
      size_t price;
      std::cin >> number >> price;
      if (number <= total_length && prices[number] < price) {
        prices[number] = price;
      }
      inserted.emplace_back(number);
    }
     sort(inserted.begin(), inserted.end());
//    auto ins_itr = inserted.begin();
     for (size_t i = 2; i <= total_length; ++i) {
//       size_t old = prices[i];
       if (prices[i] != 0) {
         continue;
       }
       for (auto p_itr = inserted.begin(); p_itr != inserted.end() && *p_itr < i; ++p_itr) {
         if (prices[i] < prices[*p_itr] + prices[i - *p_itr]) {
           prices[i] = prices[*p_itr] + prices[i - *p_itr];
         }
       }
//       if (old != 0 && old < prices[i]) {
//         inserted.erase(std::find(ins_itr, inserted.end(), i));
//       }
     }
		std::cout << prices[total_length] << '\n';
	}
	return 0;
}