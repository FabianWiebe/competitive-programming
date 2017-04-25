#include <iostream> //needed eg. for "cin" & "cout" 
#include <unistd.h>

using namespace std; 

int main (void) { 
	int cases; 
	cin >> cases; // read n 

	for (int c=0; c<cases; c++) { 
		int m; 
		cin >> m; // read m 

		double sum=0, summand;
		
		for (int i=0; i<m; i++) { 
			cin >> summand; 
			sum += summand; 
		} 
		cout << sum << endl; // write result on stdout 
	} 
} 
