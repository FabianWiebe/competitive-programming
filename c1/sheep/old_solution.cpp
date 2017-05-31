#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <fstream>


int main (void) {
	std::ios::sync_with_stdio(false);
//  	std::cin.tie(NULL);
  //	    std::ifstream ins("sample.in");
//      std::cin.rdbuf(ins.rdbuf());
	int nodes_no, edges_no, counter;
	std::cin >> counter;
	while (--counter >= 0) {	
		std::cin >> nodes_no >> edges_no;
		int first, second;
		long weight;
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
		bool no_pos_loop = false;
		for (int k = 0; k < nodes_no && !no_pos_loop; ++k) {
			for (int i = 0; i < nodes_no && !no_pos_loop; ++i) {
				for (int j = 0; j < nodes_no && !no_pos_loop; ++j) {
					if(distances_calculated[i][k] && distances_calculated[k][j]) {
						long sum = distances[i][k] + distances[k][j];
						if (i == j && sum > 0) {
							no_pos_loop = true;
							break;
						}
						if(!distances_calculated[i][j] || distances[i][j] < sum) {
							distances[i][j] = sum;
							distances_calculated[i][j] = true;
						}
					}
				}
			}
		}
		std::cout << !no_pos_loop << '\n';
	}
	return 0;
}
