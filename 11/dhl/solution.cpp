#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <algorithm>
#include <limits>

using namespace std;
vector<unsigned char> p_left;
vector<unsigned char> p_right;
unordered_map<size_t, int> m;

inline size_t get_hash(const unsigned int first, const unsigned int second, const unsigned int third, const unsigned int fourth) {
  return (size_t(first) << 48) + (size_t(second) << 32) + (size_t(third) << 16) + fourth;
}

int _min(const unsigned int first_l, const unsigned int first_r, const unsigned int last_l, const unsigned int last_r, const int max) {
  if (max < 0) {
    return -1;
  }
  auto hash = get_hash(first_l, first_r, last_l, last_r);
  auto find = m.find(hash);
  if (find != m.end()) {
    return find->second;
  }
  int min = 0;
  if (first_l == last_l) {
    for (size_t i = first_r; i<= last_r; ++i) {
      min += p_right[i];
    }
    min *= p_left[first_l];
  } else if (first_r == last_r) {
    for (size_t i = first_l; i<= last_l; ++i) {
      min += p_left[i];
    }
    min *= p_right[first_r];
  } else if (p_left[first_l] >= p_left[first_l+1] && p_right[first_r] >= p_right[first_r+1]) {
    int own = int(p_left[first_l]) * p_right[first_r];
    int tmp = _min(first_l+1, first_r+1, last_l, last_r, max - own);
    if (tmp < 0) {
      return -1;
    }
    min = own + tmp;
  } else if (p_left[last_l] >= p_left[last_l-1] && p_right[last_r] >= p_right[last_r-1]) {
    int own = int(p_left[last_l]) * p_right[last_r];
    int tmp = _min(first_l, first_r, last_l-1, last_r-1, max - own);
    if (tmp < 0) {
      return -1;
    }
    min = own + tmp;
  } else {
    int own = int(p_left[first_l]) * p_right[first_r];
    int tmp = _min(first_l+1, first_r+1, last_l, last_r, max - own);
    if (tmp < 0) {
      return -1;
    }
    min = own + tmp;
    int tmp_sum = p_left[first_l];
    for (size_t i = first_l+1; i < last_l; ++i) {
      tmp_sum += p_left[i];
      own = tmp_sum * p_right[first_r];
      if (own >= max) {
        break;
      }
      tmp = _min(i+1, first_r+1, last_l, last_r, max - own);
      if (tmp < 0) {
        continue;
      }
      min = std::min(min, tmp + own);
    }
    tmp_sum = p_right[first_r];
    for (size_t i = first_r+1; i < last_r; ++i) {
      tmp_sum += p_right[i];
      own = tmp_sum * p_left[first_l];
      if (own >= max) {
        break;
      }
      tmp = _min(first_l+1, i+1, last_l, last_r, max - own);
      if (tmp < 0) {
        continue;
      }
      min = std::min(min, tmp + own);
    }
  }
  if (min < 0) {
    return -1;
  }
  m[hash] = min;
  return min;
}

int main (void) {
	std::ios::sync_with_stdio(false);
 std::cin.tie(NULL);
//	 std::ifstream in("sample.in");
//	 std::cin.rdbuf(in.rdbuf());
	int total_number;
	std::cin >> total_number;
	while (--total_number >= 0) {
    m.clear();
    unsigned int parcel_no;
    cin >> parcel_no;
    p_left.resize(parcel_no);
    p_right.resize(parcel_no);
    for (auto itr = p_left.begin(); itr != p_left.end(); ++itr) {
      int tmp;
      cin >> tmp;
      *itr = tmp - 1;
    }
    for (auto itr = p_right.begin(); itr != p_right.end(); ++itr) {
      int tmp;
      cin >> tmp;
      *itr = tmp - 1;
    }
    int max = 0;
    for (auto itr = p_left.begin(), itr_r = p_right.begin(); itr != p_left.end(); ++itr) {
      max += int(*itr) * *itr_r;
      ++itr_r;
    }    
    // vector<unsigned int> & _p_left = p_left;
    // vector<unsigned int> & _p_right = p_right;
    int _max = _min(0, 0, parcel_no-1, parcel_no-1, max);
		std::cout << _max << '\n';
	}
	return 0;
}