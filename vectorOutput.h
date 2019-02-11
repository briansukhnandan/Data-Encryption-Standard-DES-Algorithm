#include <vector>
#include <iostream>

void printArray(std::vector<bool> a) {
	
	for (int i = 0; i < a.size(); i++) {
		
		std::cout << a[i];
		
		if ((i+1) % 8 == 0) {
		//	cout << endl;
		} 
				
	}
		
}

void print2dBoolVec(std::vector<std::vector<bool> > x) {
	
	for (size_t i = 0; i < x.size(); i++) {
		
//		std::cout << "Subkey " << i+1 <<": ";
		
		for (size_t j = 0; j < x[0].size(); j++) {
			
			std::cout << x[i][j];
			
			
		}
		std::cout << std::endl;
	}
	
	
}

void print2dBoolVecNoLine(std::vector<std::vector<bool> > x) {
	
	for (size_t i = 0; i < x.size(); i++) {
		
//		std::cout << "Subkey " << i+1 <<": ";
		
		for (size_t j = 0; j < x[0].size(); j++) {
			
			std::cout << x[i][j];
			
			
		}
//		std::cout << std::endl;
	}
	
	
}
