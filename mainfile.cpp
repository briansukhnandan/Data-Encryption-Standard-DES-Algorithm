#include <iostream>
#include <string>
#include <vector>
#include <bitset>
using namespace std;

//#include "permutationTables.h"
//Already defined in vectorOutput.h
//We aren't inherently permutating
//anything in main so this can be excluded
//from inclusion.

#include "vectorOutput.h"
#include "vectorOperations.h"
#include "binaryOperations.h"
#include "keyExpansion.h"

//Global variables for DES permutations
int bit56Permutation[56] = { 57, 49, 41, 33, 25, 17, 9, 1,
                        	 58, 50, 42, 34, 26, 18, 10, 2,
                        	 59, 51, 43, 35, 27, 19, 11, 3,
                        	 60, 52, 44, 36, 63, 55, 47, 39,
                        	 31, 23, 15, 7, 62, 54, 46, 38,
                        	 30, 22, 14, 6, 61, 53, 45, 37,
                        	 29, 21, 13, 5, 28, 20, 12, 4 };
                        	 
int subKeyPermTable[48] = { 14, 17, 11, 24, 1, 5, 
							3, 28, 15, 6, 21, 10,
						 	23, 19, 12, 4, 26, 8,
							16, 7, 27, 20, 13, 2,
							41, 52, 31, 37, 47, 55,
							30, 40, 51, 45, 33, 48,
							44, 49, 39, 56, 34, 53,
							46, 42, 50, 36, 29, 32 };
							
int bit64Permutation[64] = { 58, 50, 42, 34, 26, 18, 10, 2, 
							 60, 52, 44, 36, 28, 20, 12, 4, 
							 62, 54, 46, 38, 30, 22, 14, 6,
							 64, 56, 48, 40, 32, 24, 16, 8, 
							 57, 49, 41, 33, 25, 17, 9, 1, 
							 59, 51, 43, 35, 27, 19, 11, 3, 
							 61, 53, 45, 37, 29, 21, 13, 5,
							 63, 55, 47, 39, 31, 23, 15, 7 };
							 
int expansionTable[48] = { 32, 1, 2, 3, 4, 5,
						   4, 5, 6, 7, 8, 9,
						   8, 9, 10, 11, 12, 13,
						   12, 13, 14, 15, 16, 17,
						   16, 17, 18, 19, 20, 21,
						   20, 21, 22, 23, 24, 25,
						   24, 25, 26, 27, 28, 29,
						   28, 29, 30, 31, 32, 1};

//Key we're working with: ABCDEFGH
//In binary this is : which is 64 bits long.
// 01000001
// 01000010
// 01000011
// 01000100
// 01000101
// 01000110
// 01000111
// 01001000

int main() {
    
    string stringKey = "ABCDEFGH";
    
    string newBinaryKey = stringToBinary(stringKey);

    vector<bool> initial64KeyVector;
    
    insertBinaryVector(newBinaryKey, initial64KeyVector);
    
    cout << endl << "Original 64-bit key: ";
    
    for (int i = 0; i < initial64KeyVector.size(); i++) {
        
        cout << initial64KeyVector[i];
        
    }
    cout << endl;
	cout << endl;

//-----------------------------Generating subkeys---------------------------//
//--------------------------------------------------------------------------//
	
	//firstPermutatedVec now contains 56 bits of data.
	vector<bool> initial56KeyVector = initialPermutation(initial64KeyVector, bit56Permutation);  
	
	vector<vector<bool>> listOfSubkeys;
	
	vector<bool> shiftedsubKeybeforePerm = newShiftedVector(initial56KeyVector);

	string SubKeyStringbeforePerm;
	vector<bool> subKey;
	
	for (int j = 0; j < 16; j++) {
		
		if ((j+1) == 1 || (j+1) == 2 || (j+1) == 9 || (j+1) == 16) {
			
			SubKeyStringbeforePerm = boolVecToString(shiftedsubKeybeforePerm);
			
			cout << "Shifted 56-bit key used to get Subkey (Pre-permutation) " << (j+1) << " " << SubKeyStringbeforePerm << endl << endl;
		
			subKey = subKeyPermutations(SubKeyStringbeforePerm, subKeyPermTable);
		
			listOfSubkeys.push_back(subKey);
		
			shiftedsubKeybeforePerm = newShiftedVector(shiftedsubKeybeforePerm);
			
		}
		
		else {
			
			SubKeyStringbeforePerm = boolVecToString(shiftedsubKeybeforePerm);
			
			cout << "Shifted 56-bit key used to get Subkey (Pre-permutation) " << (j+1) << " " << SubKeyStringbeforePerm << endl << endl;
			
			subKey = subKeyPermutations(SubKeyStringbeforePerm, subKeyPermTable);
		
			listOfSubkeys.push_back(subKey);
		
			shiftedsubKeybeforePerm = new2ShiftedVector(shiftedsubKeybeforePerm);
			
		}
		
	}
	
	cout << "List of Subkeys: " << endl;
	print2dBoolVec(listOfSubkeys);
	cout << endl;

//----------------------------------------------------------------------
//----------------------------------------------------------------------
	
	//Now that we have our subkeys, we can now begin the DES
	//with the original 64 bit key message.
	
	vector<bool> permutated64Key = originalKeyPermutation(initial64KeyVector, bit64Permutation);
	printArray(permutated64Key);
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
      
    return 0;
}

