#include <vector>
#include <iostream>

void print2dBoolVec(std::vector<std::vector<bool> > x) {
	
	for (size_t i = 0; i < x.size(); i++) {
		

		
		for (size_t j = 0; j < x[0].size(); j++) {
			
			std::cout << x[i][j];
			
			
		}
		std::cout << std::endl;
	}
	
	
}

void print2dBoolVecNoLine(std::vector<std::vector<bool> > x) {
	
	for (size_t i = 0; i < x.size(); i++) {
		
		
		for (size_t j = 0; j < x[0].size(); j++) {
			
			std::cout << x[i][j];
			
			
		}

	}
	
	
}
