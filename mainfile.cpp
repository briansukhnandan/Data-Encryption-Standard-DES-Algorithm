#include <iostream>
#include <string>
#include <vector>
#include <bitset>
using namespace std;

//#include "permutationTables.h"
#include "vectorOutput.h"
#include "vectorOperations.h"
#include "binaryOperations.h"

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
	vector<bool> initial56KeyVector = initialPermutation(initial64KeyVector);  
	
	vector<vector<bool>> listOfSubkeys;
	
	vector<bool> shiftedsubKeybeforePerm = newShiftedVector(initial56KeyVector);

	string SubKeyStringbeforePerm;
	vector<bool> subKey;
	
	for (int j = 0; j < 16; j++) {
		
		if ((j+1) == 1 || (j+1) == 2 || (j+1) == 9 || (j+1) == 16) {
			
			SubKeyStringbeforePerm = boolVecToString(shiftedsubKeybeforePerm);
			
			cout << "Shifted 56-bit key used to get Subkey (Pre-permutation) " << (j+1) << " " << SubKeyStringbeforePerm << endl << endl;
		
			subKey = subKeyPermutations(SubKeyStringbeforePerm);
		
			listOfSubkeys.push_back(subKey);
		
			shiftedsubKeybeforePerm = newShiftedVector(shiftedsubKeybeforePerm);
			
		}
		
		else {
			
			SubKeyStringbeforePerm = boolVecToString(shiftedsubKeybeforePerm);
			
			cout << "Shifted 56-bit key used to get Subkey (Pre-permutation) " << (j+1) << " " << SubKeyStringbeforePerm << endl << endl;
			
			subKey = subKeyPermutations(SubKeyStringbeforePerm);
		
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
	
	vector<bool> permutated64Key = originalKeyPermutation(initial64KeyVector);
	printArray(permutated64Key);
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
      
    return 0;
}

