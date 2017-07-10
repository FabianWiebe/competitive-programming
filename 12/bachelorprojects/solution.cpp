#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

struct Edge {
    int from;
    int to;
    int weight;
    size_t id;
    int original;
};

int main (void) {
	std::ios::sync_with_stdio(false);
  std::cin.tie(NULL);
//	 std::ifstream in("largeSample.in");
//	 std::cin.rdbuf(in.rdbuf());
	int student_no, project_no, priorities, no_students_pre_project;
  cin >> student_no >> project_no >> priorities >> no_students_pre_project;
  vector<vector<int>> prios(student_no);
  vector<int> current_students;
  vector<int> student_projects(student_no);
  current_students.reserve(student_no);
  for (size_t i = 0; i < student_no; ++i) {
    int student_id;
    cin >> student_id;
    current_students.push_back(student_id);
    prios[student_id].resize(priorities);
    for (auto inner_itr = prios[student_id].begin(); inner_itr != prios[student_id].end(); ++inner_itr) {
      cin >> *inner_itr;
    }
	}
  vector<int> projects(project_no, 0);
  vector<int> next_students;
//  next_students.reserve(student_no);
//  for (size_t i = 0; i < priorities; ++i) {
//    next_students.clear();
//    for (auto student_id : current_students) {
//      if (projects[prios[student_id][i]] < no_students_pre_project) {
//        ++projects[prios[student_id][i]];
//        student_projects[student_id] = prios[student_id][i];
//      } else {
//        next_students.push_back(student_id);
//      }
//    }
//    current_students = next_students;
//  }
  int current_project_id = 0;
  for (auto student_id : current_students) {
    while(projects[current_project_id] == no_students_pre_project) {
      ++current_project_id;
    }
    ++projects[current_project_id];
    student_projects[student_id] = current_project_id;
  }

  // initialisiere graph
  vector<Edge> edges;
  edges.reserve(student_no * project_no);
  for (int student_id = 0; student_id < student_no; ++student_id) {
    int current_size = edges.size();
    for (int project_id = student_no; project_id < student_no + project_no; ++project_id) {
      edges.push_back({student_id, project_id, 2 * priorities, edges.size(), project_id - student_no + 1000});
    }
    for (int prio_id = 0; prio_id < priorities; ++prio_id) {
      edges[current_size + prios[student_id][prio_id]].weight = prio_id + 1;
    }
    Edge & current_edge = edges[current_size + student_projects[student_id]];
    int tmp = current_edge.from;
    current_edge.from = current_edge.to;
    current_edge.to = tmp;
    current_edge.weight *= -1;
  }

  bool relaxed = true;
  vector<int> dist;
  vector<int> prev;
  vector<bool> relaxed_ids;
  int counter = 0;
  while (relaxed) {
//    cerr << "Iteration: " << ++counter << endl;
    dist.clear();
    dist.resize(student_no + project_no, 0);
    prev.clear();
    prev.resize(student_no + project_no, -1);
    relaxed = true;
    for (size_t i = 1; (i < student_no + project_no) && relaxed; ++i) {
      relaxed = false;
      for (auto & edge : edges) {
        if (dist[edge.to] > dist[edge.from] + edge.weight) {
          dist[edge.to] = dist[edge.from] + edge.weight;
          prev[edge.to] = edge.id;
          relaxed = true;
        }
      }
    }
    if (relaxed) {
      relaxed_ids.clear();
      relaxed_ids.resize(student_no + project_no, false);
      for (auto & edge : edges) {
        if (dist[edge.to] > dist[edge.from] + edge.weight) {
          dist[edge.to] = dist[edge.from] + edge.weight;
          prev[edge.to] = edge.id;
          relaxed_ids[edge.to] = true;
        }
      }
      for (size_t i = 0; i < relaxed_ids.size(); ++i) {
        if (!relaxed_ids[i]) {
          continue;
        }
        int last_id = i;
        vector<bool> tmp(student_no + project_no, false);
        for (size_t j = 0; j < student_no + project_no; ++j) {
          if (tmp[last_id]) {
            break;
          }
          tmp[last_id] = true;
          last_id = edges[prev[last_id]].from;
        }
        if (!relaxed_ids[last_id]) {
          continue;
        }
        int current_id = last_id;
        relaxed_ids[i] = false;
        do {
          Edge & current_edge = edges[prev[current_id]];
          int tmp = current_edge.from;
          current_edge.from = current_edge.to;
          current_edge.to = tmp;
          current_edge.weight *= -1;
//          cerr << "relaxed_ids[" << current_id << "] = false   i = " << i << endl;
          relaxed_ids[current_id] = false;
          current_id = current_edge.to;
        } while (current_id != last_id);
      }
    }
  }
  for (auto & edge : edges) {
    if (edge.weight < 0) {
      cout << edge.to << ' ' << (edge.from - student_no) << '\n';
    }
  }

	return 0;
}