#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <algorithm>

using namespace std;
size_t stack_counter;
vector<size_t> lengths;
vector<vector<size_t>> chips;
unordered_map<uint64_t , size_t> m;

inline uint64_t get_hash(const vector<size_t> & t) {
  uint64_t result = t.front();
  for(size_t i = 1; i < stack_counter; ++i)
  {
    result <<= 10;
    result += t[i];
  }
  return result;
}

size_t max_o(const vector<size_t> & t) {

  auto find = m.find(get_hash(t));
  if (find != m.end()) {
    return find->second;
  }
  size_t max = 0;
  vector<bool> used(stack_counter, false);

  for (size_t i = 0; i < stack_counter; ++i) {
    if (used[i] || t[i] == 0) {
      continue;
    }
    size_t current = chips[i][t[i]-1];
    vector<size_t> oth {i};
    used[i] = true;
    for (size_t j = i + 1; j < stack_counter; ++j) {
      if (t[j] > 0 && chips[j][t[j]-1] == current) {
        oth.push_back(j);
        used[j] = true;
      }
    }
    vector<vector<size_t>> subset;
    vector<size_t> empty;
    subset.push_back( empty );
    for (size_t k = 0; k < oth.size(); ++k)
    {
      vector<vector<size_t>> subsetTemp = subset;
      for (size_t j = 0; j < subsetTemp.size(); ++j) {
        subsetTemp[j].push_back( oth[k] );
      }
      for (size_t j = 0; j < subsetTemp.size(); ++j) {
        subset.push_back( subsetTemp[j] );
      }
    }
    for (auto & v : subset) {
      if (v.empty()) {
        continue;
      }
      vector<size_t> n(t.begin(), t.end());
      for ( auto i : v) {
        --n[i];
      }
      size_t tmp = max_o(n) + (v.size() > 1 ? 1 << (v.size() - 2) : 0);
      if (tmp > max) {
        max = tmp;
      }
    }
  }
  m[get_hash(t)] = max;
  return max;
}

int main (void) {
	std::ios::sync_with_stdio(false);
 std::cin.tie(NULL);
//	 std::ifstream in("sample.in");
//	 std::cin.rdbuf(in.rdbuf());
	int total_number;
  vector<unsigned long> prices;
	std::cin >> total_number;
	while (--total_number >= 0) {
    m.clear();
    cin >> stack_counter;
    lengths.resize(stack_counter);
    for (auto itr = lengths.begin(); itr != lengths.end(); ++itr) {
      cin >> *itr;
    }
    chips.resize(stack_counter);
    auto chips_itr = chips.begin();
    for (auto itr_lengths = lengths.begin(); itr_lengths != lengths.end(); ++itr_lengths) {
      chips_itr->resize(*itr_lengths);
      for (auto itr = chips_itr->begin(); itr != chips_itr->end(); ++itr) {
        cin >> *itr;
      }
      ++chips_itr;
    }
		std::cout << max_o(lengths) << '\n';
	}
	return 0;
}