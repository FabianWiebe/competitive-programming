#include <iostream>
#include <vector>
#include <fstream>
#include <utility>
#include <algorithm>
#include <iomanip>
#include <limits>
#include <cmath>
#include <set>

using namespace std;

struct Job {
    int duration;
    int deadline;
    vector<int> deps;
};

struct Entry {
    Entry(int _id, Entry* _next, Entry* _prev) : id(_id), next(_next), prev(_prev) {};
    int id;
    Entry* next;
    Entry* prev;
};

int main (void) {
	 std::ios::sync_with_stdio(false);
   std::cin.tie(NULL);
  ifstream in("largeSample.in");
  cin.rdbuf(in.rdbuf());
	int total_number;
	cin >> total_number;
  vector<Job> jobs;
  vector<int> ind;
	while (--total_number >= 0) {
    int job_no;
    cin >> job_no;
    jobs.resize(job_no);
    ind.resize(job_no);
    auto ind_itr = ind.begin();
    for (size_t i = 0; i < job_no; ++i) {
      *ind_itr = i;
      ++ind_itr;
    }
    for (auto job_itr = jobs.begin(); job_itr != jobs.end(); ++job_itr) {
      int deps_no;
      cin >> job_itr->duration >> job_itr->deadline >> deps_no;
      auto & deps = job_itr->deps;
      deps.resize(deps_no);
      for (auto itr = deps.begin(); itr != deps.end(); ++itr) {
        cin >> *itr;
      }
    }

    sort(ind.begin(), ind.end(), [&](int ind1, int ind2) {
        auto & job1 = jobs[ind1];
        auto & job2 = jobs[ind2];
       if (job1.deadline == job2.deadline) {
         return job1.duration < job2.duration;
       }
        return job1.deadline < job2.deadline;


    });
    vector<bool> fixed(job_no, false);

    Entry *current = new Entry{ind[0], nullptr, nullptr};
    Entry *first = current;
    for (size_t i = 1; i < job_no; ++i) {
      Entry *tmp = new Entry{ind[i], nullptr, current};
      current->next = tmp;
      current = tmp;
    }

    int fixed_counter = 0;

    while (current != nullptr) {
      int index = current->id;
      auto & job = jobs[index];
      if (job.deps.empty()) {
        fixed[index] = true;
        current = current->prev;
        ++fixed_counter;
      } else {
//        cerr << "start new set " << endl << endl << endl;
        set<int> visited;
        int insert_counter = 0;
        Entry* tmp = current;
        current = current->prev;
        bool moved = false;
        for (auto dep : job.deps) {
          auto search = visited.find(dep);
          while (fixed[dep] && search == visited.end()) {
            moved = true;
            if (tmp->next == nullptr) {
              cout << "visited size " << visited.size() << endl;
              cout << "";
            }
            int current_id = tmp->prev->id;
            if (visited.find(current_id) != visited.end()) {
              cerr << "not pos" << endl;
            }
//            cerr << "inserted " << current_id << "   : " << ++insert_counter << endl;
            visited.insert(current_id);
            if (tmp->prev != nullptr) {
              tmp->prev->next = tmp->next; // 1
            }
            tmp->next->prev = tmp->prev; // 2
            if (tmp->next->next != nullptr) {
              tmp->next->next->prev = tmp; // 6
            }
            tmp->prev = tmp->next; // 4
            tmp->next = tmp->next->next; // 5
            tmp->prev->next = tmp; // 3
            if (current_id == dep) {
              break;
            }
          }
        }
//        if (!moved) {
          fixed[index] = true;
        fixed_counter++;
//        }
      }
    }
    while (first->prev != nullptr) {
      first = first->prev;
    }
  int time = 0;
    int over = 0;
    current = first;
    while (current != nullptr) {
      auto & job = jobs[current->id];
      time += job.duration;
      if (job.deadline < time) {
        over = max(over, time - job.deadline);
      }
      auto tmp = current;
      current = current->next;
      delete tmp;
    }
    cout << over << '\n';
	}
	return 0;
}