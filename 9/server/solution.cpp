#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <unordered_set>
#include <queue>
#include <<cstdlib>>

using namespace std;

using my_pair_t = std::pair<size_t, size_t>;

using my_container_t = std::vector<my_pair_t>;

struct Slot {
    size_t server_id;
    size_t start;
    size_t end;
};
using Pair = pair<int, int>;


int main (void) {
	std::ios::sync_with_stdio(false);
  std::cin.tie(NULL);
//	 std::ifstream in("largeSample.in");
//	 std::cin.rdbuf(in.rdbuf());
	int total_number;
	std::cin >> total_number;
  vector<Slot> slots;
  unordered_set<unsigned long> result;
  vector<Pair> current;
	while (--total_number >= 0) {
    result.clear();
    size_t server_no, timeslot_no;
    cin >> server_no >> timeslot_no;
    current.clear();
    current.resize(server_no, Pair(-1, -1));
    slots.clear();
    slots.resize(timeslot_no);
    for (auto itr = slots.begin(); itr != slots.end(); ++itr) {
      size_t server_id, start, end;
      cin >> server_id >> start >> end;
      if (end <= start) {
        continue;
      }
      *itr = Slot{server_id, start, end};
    }
    sort(slots.begin(), slots.end(), [](const Slot & s1, const Slot & s2){
        if (s1.start == s2.start) {
          return s1.server_id < s2.server_id;
        }
        return s1.start < s2.start;
    });

    int current_time = 0;
    auto my_comp =
            [](const my_pair_t& e1, const my_pair_t& e2)
            {
                if (e1.second == e2.second) {
                  return e1.first > e2.first;
                }
                return e1.second > e2.second; };
    priority_queue<my_pair_t,
            my_container_t,
            decltype(my_comp)> queue(my_comp);

    int first = -1;
    int last = -1;
    int runner = first;

    vector<size_t> updated;
    for (auto & s : slots) {
      if (s.start > current_time) {
        for (auto & update : updated) {
            if (current[update].second != -1) {
              unsigned long value = (static_cast<unsigned long>(update) << 32) + current[update].second;
              result.insert(value);
            }
            if (current[update].first != -1) {
              unsigned long value = (static_cast<unsigned long>(current[update].first) << 32) + update;
              result.insert(value);
            }
          }
        updated.clear();
        while (!queue.empty() && queue.top().second < s.start) {
          int last_time = queue.top().second;

          while (!queue.empty() && queue.top().second == last_time) {
            auto p = queue.top();
            queue.pop();
            if (last == p.first) {
              last = current[p.first].first;
              if (updated.back() == p.first) {
                updated.pop_back();
              }
            } else {
              current[current[p.first].second].first = current[p.first].first;
              if (first != p.first) {
                if (updated.back() == p.first) {
                  updated.back() = current[p.first].second;
                } else {
                  updated.push_back(current[p.first].second);
                }
              }
            }
            if (first == p.first) {
              first = current[p.first].second;
            } else {
              current[current[p.first].first].second = current[p.first].second;
            }
            current[p.first] = Pair(-1, -1);
          }

          for (auto & update : updated) {
              unsigned long value = (static_cast<unsigned long>(current[update].first) << 32) + update;
              result.insert(value);
          }
          updated.clear();
        }


        runner = first;
      }
      current_time = s.start;
      queue.emplace(s.server_id, s.end);
      if (runner == -1) {
        first = last = runner = s.server_id;
      } else if (runner > s.server_id) {
        current[s.server_id] = Pair{-1, runner};
        current[runner].first = s.server_id;
        first = runner = s.server_id;

      } else {
        while (current[runner].second != -1 && current[runner].second < s.server_id) {
          runner = current[runner].second;
        }
        if (current[runner].second == -1) {
          current[s.server_id] = Pair{runner, -1};
          current[runner].second = s.server_id;
          last = s.server_id;
        } else {
          current[s.server_id] = Pair{runner, current[runner].second};
          current[current[runner].second].first = s.server_id;
          current[runner].second = s.server_id;
        }
        runner = s.server_id;

      }
      updated.push_back(s.server_id);
    }

    for (auto & update : updated) {
      if (current[update].second != -1) {
        unsigned long value = (static_cast<unsigned long>(update) << 32) + current[update].second;
        result.insert(value);
      }
      if (current[update].first != -1) {
        unsigned long value = (static_cast<unsigned long>(current[update].first) << 32) + update;
        result.insert(value);
      }
    }
    updated.clear();

    while (!queue.empty()) {
      int last_time = queue.top().second;

      while (!queue.empty() && queue.top().second == last_time) {
        auto p = queue.top();
        queue.pop();

        if (last == p.first) {
          last = current[p.first].first;
          if (updated.back() == p.first) {
            updated.pop_back();
          }
        } else {
          current[current[p.first].second].first = current[p.first].first;
          if (first != p.first) {
            if (updated.back() == p.first) {
              updated.back() = current[p.first].second;
            } else {
              updated.push_back(current[p.first].second);
            }
          }
        }
        if (first == p.first) {
          first = current[p.first].second;
        } else {
          current[current[p.first].first].second = current[p.first].second;
        }
        current[p.first] = Pair(-1, -1);
      }

      for (auto & update : updated) {
        unsigned long value = (static_cast<unsigned long>(current[update].first) << 32) + update;
        result.insert(value);
      }
      updated.clear();
    }

    vector<Pair> sorted_result(result.size());
    auto sr_itr = sorted_result.begin();
    for (auto p : result) {
      *sr_itr = make_pair(p >> 32, (p << 32)>>32);
      ++sr_itr;
    }
    sort(sorted_result.begin(), sorted_result.end(), [](Pair const & lhs,  Pair const & rhs) {
      if (lhs.first == rhs.first) {
        return lhs.second < rhs.second;
      }
      return lhs.first < rhs.first;
    });

		std::cout << sorted_result.size() << '\n';
    for (const auto & p : sorted_result) {
      cout << p.first << ' ' << p.second << '\n';
    }
    cout << flush;
	}
	return 0;
}