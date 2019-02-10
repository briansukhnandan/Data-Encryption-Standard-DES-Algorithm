#include <vector>
#include <stdio.h>

//The two vectors must be the same size.
std::vector<bool> xorCipher(std::vector<bool> x, std::vector<bool> y) {
	
	std::vector<bool> z;
	int size = x.size();
	
	for (size_t i = 0; i < size; i++) {
		
		if (x[i] == true && y[i] == true) {
			z.push_back(false);
		}
		
		else if (x[i] == false && y[i] == false) {
			z.push_back(false);
		}
		
		else {
			z.push_back(true);
		}
		
	}
	
	return z;
}

std::vector<bool> expansionOfKey(std::vector<bool> x, std::vector<std::vector<bool>> subKeyList, int permTable[]) {
	//Split permutated 64-bit key into half.
	//We now have a left side and right side.
	//We are going to expand the 32 bit right side half
	//With the expansion table, thus giving it 48 bits.
	
	int a[32]; //First 32 bits
	int b[32]; //Last 32 bits that we perform operations on.
	
	//With this 48-bit expansion, we are going to perform
	//an xor with the subkey of what round we're on,
	//and then shrink it back to 32-bits using another
	//table.
	
	std::vector<bool> z;
	
	//TODO
	//Copies elements over into a and b.
	for (int i = 0; i < 32; i++) {	
		a[i] = x[i];		
	}
	for (int i = 32; i < 64; i++) {
		b[i] = x[i];
	}
	
	for (int i = 0; i < 48; i++) {
		
		if ( (b[permTable[i] - 1]) == '1') {
    		
    		z.push_back(true);
    		
		} else {
			
			z.push_back(false);
			
		}
		
	}
	//Z should now contained the permutated 48 bits, which we now
	//perform an XOR on.
	
	
}


