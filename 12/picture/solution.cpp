#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

using Pair = pair<int, int>;

long merge_sort(int index_first, int index_last, vector<int> & students_from, vector<int> & students_to) {
  long distance = 0;
  if (index_last - index_first < 10) {
//     insertion sort
    int i = index_first;
    while (i < index_last) {
      while (i < index_last && students_to[i] >= students_to[i + 1]) {
        ++i;
      }
      if (i >= index_last) {
        break;
      }
      int j = i + 1;
      while (j > index_first && students_to[j] > students_to[j - 1]) {
        int tmp = students_to[j];
        students_to[j] = students_to[j - 1];
        students_to[j - 1] = tmp;

        ++distance;
        --j;
      }
      ++i;
      if (i >= index_last) {
        break;
      }
    }
    return distance;
  }
  // merge sort
  int middle = (index_first + index_last) / 2;
  distance += merge_sort(index_first, middle, students_to, students_from);
  distance += merge_sort(middle + 1, index_last, students_to, students_from);
  int first = index_first;
  int second = middle + 1;
  auto itr_out = students_to.begin() + index_first;
  int out_count = index_first;
  while (first <= middle || second <= index_last) {
    while (first <= middle && (second > index_last || students_from[first] >= students_from[second])) {
      *itr_out++ = students_from[first];
      ++out_count;
      ++first;
    }
    if (second <= index_last) {
      *itr_out++ = students_from[second];
      distance += second - out_count;
      ++out_count;
      ++second;
    }

  }
  return distance;
}

int main (void) {
	std::ios::sync_with_stdio(false);
  std::cin.tie(NULL);
//	 std::ifstream in("sample.in");
//	 std::cin.rdbuf(in.rdbuf());
	int total_number;
  cin >> total_number;

  vector<int> students1;
  vector<int> students2;

	while (--total_number >= 0) {
    int number_students;
    cin >> number_students;
    students1.resize(number_students);
    students2.resize(number_students);
    int counter = 0;
    for (auto itr = students1.begin(); itr != students1.end(); ++itr) {
//      int position;
      cin >> *itr;
//      *itr = make_pair(number_students - position, counter++);
    }
    if (number_students < 2) {
      cout << '0' << '\n';
      continue;
    } else if (number_students == 2) {
      if (students1[1] > students1[0]) {
        cout << '1' << '\n';
      } else {
        cout << '0' << '\n';
      }
      continue;
    }
    copy(students1.begin(), students1.end(), students2.begin());
//    sort(students.begin(), students.end(), [](const Pair & p1, const Pair & p2) {
//        if (p1.first == p2.first) {
//          return p2.second < p2.second;
//        }
//        return p1.first < p2.first;
//    });
//    int from_right = 0;
//    long distance = 0;
//    counter = 0;
//    for (auto student : students) {
//      if (student.first == student.second) {
//        distance += from_right;
//      } else if (student.first < student.second) {
//        distance += student.second - student.first + from_right;
//        ++from_right;
//      } else {
//        --from_right;
//        distance += from_right;
//      }
//    }

    cout << merge_sort(0, number_students - 1, students1, students2) << '\n';
	}
	return 0;
}