#include <vector>
#include <stdio.h>



//The two vectors must be the same size.
std::vector<bool> xorCipher(std::vector<bool>&x, std::vector<bool> y) {
	
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

std::vector<bool> expansionOfKey(std::vector<bool> x, std::vector<std::vector<bool>> subKeyList, int permTable[], int index) {
	//Split permutated 64-bit key into half.
	//We now have a left side and right side.
	//We are going to expand the 32 bit right side half
	//With the expansion table, thus giving it 48 bits.
	
	std::vector<bool> a; //First 32 bits
	std::vector<bool> b; //Last 32 bits that we perform operations on.
	
	std::vector<bool> indexedSubkey; //Stores the current subkey.
	
	for (int i = 0; i < subKeyList[index].size(); i++) {
		
		indexedSubkey.push_back(subKeyList[index][i]);
		
	}
	
	//With this 48-bit expansion, we are going to perform
	//an xor with the subkey of what round we're on,
	//and then shrink it back to 32-bits using another
	//table.
	
	std::vector<bool> z;
	
	//TODO
	//Copies elements over into a and b.
	for (int i = 0; i < 64; i++) {	
		
		if (i < 32) a.push_back(x[i]);
		
		else b.push_back(x[i]);
		
		
	}
	
	
	for (int i = 0; i < 48; i++) {
		
		if ( (b[permTable[i] - 1]) == true) {
    		
    		z.push_back(true);
    		
		} else {
			
			z.push_back(false);
			
		}
		
	}
	//Z should now contained the permutated 48 bits, which we now
	//perform an XOR on.
	xorCipher(z, indexedSubkey);
	
	
	//Return this 48 bit vector.
	return z;
}

// Starts off with the 48 bit vector from above.
// For each 6-bit block of the 48 bits (8 blocks total)
// For ex: Let's say our block was 111100.
// The outer two bits are 10 = 2 in binary. This is our row number.
// Our column number is the innermost 4 bits, which is 1110 = 14 in binary.
// We would navigate to the value at that index, lets say for example
// the number at that index is 5, then back to binary that would be
// 0101 (has to be converted back to a 4 bit array so we can end up
// with 32 bits when this function ends).

std::vector<std::vector<bool>> shrink48bitKey(std::vector<bool> x) {
	
	//Will be used to store the 32 bits.
	std::vector<bool> z;
	
	//TODO:
	int index = 0;
	std::vector<std::vector<bool>> bit6Blocks;
	
	std::vector<bool> temp;
	//Loop through 6 bit blocks
	//Store them in an array within an array.
	//Push that second order array in the original array.
	for (int i = 0; i < 8; i++) {
		
		for (int j = 0; j < 6; j++) {
			
			temp.push_back(x[index]);
			
			index++;
		}
		
		bit6Blocks.push_back(temp);
		temp.clear();	
		
	}

	//Now we have each 6-bit block 
	
	
	
	
	//TESTING: Should contain 48 bits.
	//return bit6Blocks;
}












