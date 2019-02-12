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
						   
int finalPermutation[64] = { 40, 8, 48, 16, 56, 24, 64, 32,
							 39, 7, 47, 15, 55, 23, 63, 31,
							 38, 6, 46, 14, 54, 22, 62, 30,
							 37, 5, 45, 13, 53, 21, 61, 29,			
							 36, 4, 44, 12, 52, 20, 60, 28,  
							 35, 3, 43, 11, 51, 19, 59, 27, 
							 34, 2, 42, 10, 50, 18, 58, 26, 
							 33, 1, 41, 9, 49, 17, 57, 25 };					
						   
int sBoxes[8][4][16] = { 
							{ 
								{ 14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7 },
								{ 0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8 },
								{ 4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0 },
								{ 15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13 }
										
								},
							
							{
								
								{ 15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10 },
								{ 3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5 },
								{ 0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15 },
								{ 13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9 }
									
								},
							
							{
								
								{ 10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8 },
								{ 13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1 },
								{ 13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7 },
								{ 1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12 }						
								
								},
								
							{
								{ 7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15 },
								{ 13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9 },
								{ 10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4 },
								{ 3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14 }
								
								},
								
							{
								
								{ 2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9 },
								{ 14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6 },
								{ 4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14 },
								{ 11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3 }
								
								},
								
							{
								
								{ 12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11 },
								{ 10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8 },
								{ 9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6 },
								{ 4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13 }
									
								},
								
							{
								
								{ 4, 11, 2, 14, 15, 0, 8, 13, 12, 9, 7, 5, 10, 6, 1 },
								{ 13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6 },
								{ 1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2 },
								{ 6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12 }
									
								},
								
							{
								
								{ 13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7 },
								{ 1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2 },
								{ 7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8 },
								{ 2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11 }
									
								}
							
						};

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
    
    string stringKey;
    cout << "Enter a key of length 8 (ex: ABCDEFGH): ";
    cin >> stringKey;
    cout << endl;
    
    string newBinaryKey = stringTo8Binary(stringKey);

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
	
	vector<vector<bool> > listOfSubkeys;
	
	vector<bool> shiftedsubKeybeforePerm = newShiftedVector(initial56KeyVector);

	string SubKeyStringbeforePerm;
	vector<bool> subKey;
	
	for (int j = 0; j < 16; j++) {
		
		if ((j+1) == 1 || (j+1) == 2 || (j+1) == 9 || (j+1) == 16) {
			
			SubKeyStringbeforePerm = boolVecToString(shiftedsubKeybeforePerm);
			
//			cout << "Shifted 56-bit key used to get Subkey (Pre-permutation) " << (j+1) << " " << SubKeyStringbeforePerm << endl << endl;
		
			subKey = subKeyPermutations(SubKeyStringbeforePerm, subKeyPermTable);
		
			listOfSubkeys.push_back(subKey);
		
			shiftedsubKeybeforePerm = newShiftedVector(shiftedsubKeybeforePerm);
			
		}
		
		else {
			
			SubKeyStringbeforePerm = boolVecToString(shiftedsubKeybeforePerm);
			
//			cout << "Shifted 56-bit key used to get Subkey (Pre-permutation) " << (j+1) << " " << SubKeyStringbeforePerm << endl << endl;
			
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

	cout << endl;
	
	vector<bool> bit64KeyPostRounds;
	
	for (int j = 0; j < 16; j++) {
		
		bit64KeyPostRounds = expansionOfKey(permutated64Key, listOfSubkeys, expansionTable, j, sBoxes);
		
	}
	
//	printArray(bit64KeyPostRounds);
//	cout << endl;
//	cout << endl;	
	
	//Now we have to reverse the halves, so put the last 32 as the first,
	//then first 32 as the last.
	vector<bool> reversedKey;
	
	for (int k = 0; k < 64; k++) {
		
		if (k < 32) {
			reversedKey.push_back(bit64KeyPostRounds[k+32]);
		} else {
			reversedKey.push_back(bit64KeyPostRounds[k-32]);		
		}
				
	}
	
	//Finally we permute this one last time according to the finalPermutation table
	//and we have our ciphertext.
	
	vector<bool> cipherText = finalKeyPermutation(reversedKey, finalPermutation);
	
	cout << "Ciphertext: " << endl;
	printArray(cipherText);
	cout << endl;
	   
    return 0;
}

