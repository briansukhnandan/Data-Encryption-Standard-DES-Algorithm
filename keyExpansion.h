#include <vector>
#include <stdio.h>
#include <string>
#include <bitset>
#include <algorithm>
#include <iostream>

void printArray(std::vector<bool> a) {
	
	for (int i = 0; i < a.size(); i++) {
		
		std::cout << a[i];
		
				
	}
	std::cout << std::endl;
}

void insertBinaryVector(std::string y, std::vector<bool> &z) {
    
    for (int i = 0; i < y.size(); i++) {

        if (y[i] == '0') {
            
            z.push_back(false);
            
        } else {
            
            z.push_back(true);
            
        }
        
    }
    
}

int stringofBinarytoInt(std::string s) {
	
	int a = stoi(s);
	int power = 0;
	
	int number;
	
	while (a != 0) {
		
		number += (a%10) * std::pow(2, power);
		a /= 10;
		power++;
	}
	
	return number;
}

std::string stringTo8Binary(std::string x) {
    
    std::string y = "";
    
    for (size_t i = 0; i < x.size(); i++) {
        
        //prints 8 bits binary representation of each character of the string.
        y += std::bitset<8>(x.c_str()[i]).to_string();
        
    }
    
    //Returns a string of the binary representation.
    //In c++, since strings can be treated as an array,
    //this seems like a suitable choice.
    return y;
} 

std::string stringToBinary(std::string x) {
    
    std::string y = "";
    
    for (size_t i = 0; i < x.size(); i++) {
        
        //prints 8 bits binary representation of each character of the string.
        y += std::bitset<4>(x.c_str()[i]).to_string();
        
    }
    
    //Returns a string of the binary representation.
    //In c++, since strings can be treated as an array,
    //this seems like a suitable choice.
    return y;
} 

std::string intToBinary(int x) {
    
    std::string y = "";
           
    //prints 8 bits binary representation of each character of the string.
    y += std::bitset<4>(x).to_string();
    
    //Returns a string of the binary representation.
    //In c++, since strings can be treated as an array,
    //this seems like a suitable choice.
    return y;
} 


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

//Does right half operations.
//This comes after XOR with the subkey.
//Call this function inside of expansionKey
//expansio
//std::string shrink48bitKey(std::vector<bool> x) {
std::vector<bool> shrink48bitKey(std::vector<bool> x, int sBoxes[8][4][16]) {
	
	//Will be used to store the 32 bits.
	std::vector<bool> z;
	
	int index = 0;
	std::vector<std::vector<bool> > bit6Blocks;
	
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
	std::string rowCoord = "";
	std::string colCoord = "";
	
	//Will contain the "shrunken" 4 bit blocks, obtained from bit6blocks.
	std::vector<bool> bit4Blocks;
	
	int rowCoordNumber;
	int colCoordNumber;
	
	for (int i = 0; i < bit6Blocks.size(); i++) {
		
		for (int j = 0; j < bit6Blocks[0].size(); j++) {
			
			if (j == bit6Blocks[0].size() - 1) {
				
				if (bit6Blocks[i][0] == true) rowCoord+= "1"; 
				else rowCoord+= "0";
				
				if (bit6Blocks[i][j] == true) rowCoord+= "1";
				else rowCoord+= "0";
				
				//Copies inner 4 bits into colCoord.
				for (size_t k = 1; k < bit6Blocks[0].size() - 1; k++) {
					if (bit6Blocks[i][k] == true) colCoord += "1";
					else colCoord += "0";
				}
				
				
				
			}
			
			
		}
		//TODO
		//Convert rowCoord and ColCoord to binary and then that binary to an int.
		//Take these two ints and get the number at that index at permtable.
		//Turn that index number in permtable and convert it to binary.
		//From this loop we will generate a vector<vector<bool>> (a vector that contains 8 vectors, each with 4 elements inside).
		//Also we clear rowCoord and colCoord at the end of this for the next 6 iterations
		//of that inner loop.
		
		rowCoordNumber = stringofBinarytoInt(rowCoord);
		colCoordNumber = stringofBinarytoInt(colCoord);
		
		int a = sBoxes[i][rowCoordNumber][colCoordNumber];

		//Now numbersAtsBox is a binary-string representation of the
		//integer it just was.
		std::string numberAtsBox = intToBinary(a);
		
		
		for (int i = 0; i < numberAtsBox.size(); i++) {
			if (numberAtsBox[i] == '1') bit4Blocks.push_back(true);
			else bit4Blocks.push_back(false);
		}
		
		
		rowCoord = ""; colCoord = "";
	}
	
	return bit4Blocks;
}

std::vector<bool> expansionOfKey(std::vector<bool> x, std::vector<std::vector<bool> > subKeyList, int permTable[], int index, int sBoxes[8][4][16]) {
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
	
	//Copy of the original right half.
	//This will change at every round.
	//After we perform the xor with the table data
	//and left, it will be our new right side,
	//which will be copied into here.
	std::vector<bool> copyOfB = b;
	
	
	for (int i = 0; i < 48; i++) {
		
		if ( (b[permTable[i] - 1]) == true) {
    		
    		z.push_back(true);
    		
		} else {
			
			z.push_back(false);
			
		}
		
	}
	//Z should now contained the permutated 48 bits, which we now
	//perform an XOR on.
	z = xorCipher(z, indexedSubkey);
	
	
	//Shrink z back to 32 bits.
	b = shrink48bitKey(z, sBoxes);
	b = xorCipher(a, b);
	
	std::vector<bool> bit64KeyPostRound;
	
	for (int k = 0; k < 64; k++) {
		
		if (k < 32) {
			
			bit64KeyPostRound.push_back(copyOfB[k]);
			
		} else {
			
			bit64KeyPostRound.push_back(b[k]);
			
		}
		
	}
	
	return bit64KeyPostRound;
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















