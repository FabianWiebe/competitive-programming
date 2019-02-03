#include <iostream>
#include <vector>
#include <fstream>
#include <utility>
#include <algorithm>
#include <iomanip>
#include <limits>
#include <cmath>

using namespace std;

struct Item {
    int index;
    int value;
    int weight;
};

int main (void) {
//	 std::ios::sync_with_stdio(false);
//   std::cin.tie(NULL);
//  ifstream in("sample.in");
//  cin.rdbuf(in.rdbuf());
	int total_number;
	cin >> total_number;
	while (--total_number >= 0) {
    int capacity, no;
    cin >> capacity >> no;
    vector<Item> items;
    items.reserve(no);
    int v_max = -1;
    for (int i = 0; i < no; ++i) {
      int value, weight;
      cin >> value >> weight;
//      if (weight > capacity) {
//        continue;
//      }
      if (value > v_max) {
        v_max = value;
      }
      items.push_back(Item{i, value, weight});
    }
    vector<int> out;
    int sum = 0;
    int cap = 0;

//    sort(items.begin(), items.end(), [](Item i1, Item i2) {
//        return 1. * i1.value / (double) i1.weight > 1. * i2.value / (double) i2.weight;
//    });
//
//    for (Item & i : items) {
//      if (cap + i.weight <= capacity) {
//        out.push_back(i.index);
//        sum += i.value;
//        cap += i.weight;
//      } else if (i.value > sum && i.weight <= capacity) {
//        sum = i.weight;
//        out.clear();
//        out.push_back(i.index);
//        cap = i.weight;
//      }
//    }


    double e = 0.02;
    double K = e * v_max / no;
    if (K == 0) {
      K = 1;
    }
    for (auto & item : items) {
      item.value /= K;
    }
    v_max /= K;


    vector<vector<int>> table(no);
    vector<vector<bool>> b_table(no);
    auto & b_row = b_table[0];
    b_row.resize(no*v_max + 1, false);
    auto & row = table[0];
    row.resize(no*v_max + 1, -1);
    row[items.front().value] = items.front().weight;
    b_row[items.front().value] = true;
    int max_val = items.front().value;
    for (int i = 1; i < no; ++i) {
      auto & item = items[i];
      auto & row = table[i];
      auto & b_row = b_table[i];
      row.reserve(no*v_max);
      for (int j = 0; j <= no*v_max; ++j) {
        int weight = table[i-1][j];
        int new_weight = weight;
        if (item.value <= j && table[i-1][j - item.value] != -1) {
          new_weight = table[i-1][j - item.value] + item.weight;
        }
        if (j == item.value) {
          new_weight = item.weight;
        }
        b_row.push_back(new_weight > weight);

        if (new_weight > weight) {
          weight = new_weight;
          if (j > max_val) {
            max_val = j;
          }
        }
        row.push_back(weight);
      }
    }
    int current_j = v_max;
    for (int i = no - 1; i >= 0; --i) {
      if (b_table[i][current_j]) {
        out.push_back(i);
        current_j -= items[i].value;
      }
    }
    for (int i = out.size() - 1; i > 0; --i) {
      cout << out[i] << ' ';
    }
    cout << out.front() << endl;
	}
	return 0;
}