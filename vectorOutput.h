#include <vector>
#include <iostream>

void printArray(vector<bool> a) {
	
	for (int i = 0; i < a.size(); i++) {
		
		cout << a[i];
		
		if ((i+1) % 8 == 0) {
		//	cout << endl;
		} 
				
	}
		
}

void print2dBoolVec(vector<vector<bool>> x) {
	
	for (size_t i = 0; i < x.size(); i++) {
		
		cout << "Subkey " << i+1 <<": ";
		
		for (size_t j = 0; j < x[0].size(); j++) {
			
			cout << x[i][j];
			
			
		}
		cout << endl;
	}
	
	
}
