#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <unordered_map>
#include <queue>


#include <stdio.h>

#ifdef _WIN32
#include <io.h>
#include <fcntl.h>
#define read _read
#else
#include <unistd.h>
#endif

/// IMPORTANT: Call this at the beginning of main!
void init_binio() {
#ifdef _WIN32
  _setmode(0, _O_BINARY);
#endif
}
using namespace std;

/// Helper function.
void fill_buf(uint32_t* buf, uint32_t count) {
  uint32_t remaining = count * 4;
  uint8_t* bbuf = (uint8_t*)buf;

  while (remaining > 0) {
    auto r = read(0, bbuf, remaining);
    if (r <= 0) {
      std::cerr << "Error reading input" << std::endl;
      exit(33);
    }
    remaining -= (uint32_t)r;
    bbuf += r;
  }
}

/// Read one unsigned 32bit integer from standard input.
uint32_t read_int() {
  uint32_t buf;
  fill_buf(&buf, 1);
  return buf;
}

/// Overwrite the contents of vec with `size` 32bit integers read from standard
/// input.
void read_vec(vector<uint32_t> &vec, uint32_t size) {
  vec.resize(size);
  fill_buf(vec.data(), size);
}


int main (void) {
  init_binio();
	std::ios::sync_with_stdio(false);
 std::cin.tie(NULL);
//	 std::ifstream in("largeSample.in");
//	 std::cin.rdbuf(in.rdbuf());
	int total_number = read_int();
  // cerr << "total number: " << total_number << '\n';
  vector<uint32_t> hops;
  vector<uint32_t> distances;
	while (--total_number >= 0) {
    uint32_t nodes_no = read_int();
    uint32_t start_id = read_int();
    // cerr << "nodes no: " << nodes_no << " start id: " << start_id << '\n';
    read_vec(distances, nodes_no * nodes_no);
    hops.clear();
    hops.resize(nodes_no * nodes_no, 1);
    for(size_t i = 0; i < nodes_no; ++i) {
      hops[i * nodes_no + i] = 0;
    }
    for (size_t k = 0; k < nodes_no; ++k) {
      size_t _k = k * nodes_no;
      for (size_t i = 0; i < nodes_no; ++i) {
        size_t _i = i * nodes_no;
        for (size_t j = 0; j < nodes_no; ++j) {
          uint32_t sum = distances[_i + k] + distances[_k + j];
          if (distances[_i + j] == sum) {
            uint32_t sum_hops = hops[_i + k] + hops[_k + j];
            if (hops[_i + j] < sum_hops) {
              hops[_i + j] = sum_hops;
            }
          } else if(distances[_i + j] > sum) {
            distances[_i + j] = sum;
            hops[_i + j] = hops[_i + k] + hops[_k + j];
          }
        }
      }
    }
//    for (size_t i = 0; i < nodes_no; ++i){
//      for (size_t j = 0; j < nodes_no; ++j){
//        cerr << distances[i*nodes_no + j] << "  ";
//      }
//      cerr << '\n';
//    }
//    for (size_t i = 0; i < nodes_no; ++i){
//      for (size_t j = 0; j < nodes_no; ++j){
//        cerr << hops[i*nodes_no + j] << "  ";
//      }
//      cerr << '\n';
//    }
    size_t max_id = 0;
    size_t max_hops = 0;
    size_t row = start_id * nodes_no;
    for(size_t i = 0; i < nodes_no; ++i) {
      if (hops[row + i] > max_hops) {
        max_hops = hops[row + i];
        max_id = i;
      }
    }
    // cerr << "max id: " << max_id << " max_hops: " << max_hops << endl;
		std::cout << max_id << ' ' << max_hops << endl;
	}
	return 0;
}
