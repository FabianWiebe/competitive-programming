#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <fstream>

using my_pair_t = std::pair<int,long>;
 
using my_container_t = std::vector<my_pair_t>;

int main (void) {
	std::ios::sync_with_stdio(false);
  std::cin.tie(NULL);
	int nodes_no, edges_no, question_no;
	std::cin >> nodes_no >> edges_no >> question_no;
	int first, second, weight;
	std::vector<std::vector<long>> distances(nodes_no, std::vector<long>(nodes_no));
	std::vector<std::vector<bool>> distances_calculated(nodes_no, std::vector<bool>(nodes_no, false));
  for (int i = 0; i < edges_no; ++i) {
    std::cin >> first >> second >> weight;
    distances[first][second] = weight;
    distances_calculated[first][second] = true;

	}
  for (int i = 0; i < nodes_no; ++i) {
    distances[i][i] = 0;
    distances_calculated[i][i] = true;
  }
  for (int k = 0; k < nodes_no; ++k) {
    for (int i = 0; i < nodes_no; ++i) {
      for (int j = 0; j < nodes_no; ++j) {
        if(distances_calculated[i][k] && distances_calculated[k][j]) {
          long sum = distances[i][k] + distances[k][j];
          if(!distances_calculated[i][j] || distances[i][j] > sum) {
            distances[i][j] = sum;
            distances_calculated[i][j] = true;
          }
        }
      }
    }
  }
	for (int i = 0; i < question_no; ++i) {
		std::cin >> first >> second;
		if (!distances_calculated[first][second]) {
			std::cout << "oo" << '\n';
		} else {
			std::cout << distances[first][second] << '\n';
		}
	}
	return 0;
}
