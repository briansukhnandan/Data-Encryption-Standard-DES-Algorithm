#include <iostream>
#include <string>
#include <vector>
#include <bitset>
using namespace std;

//Global variables for DES permutations
int initialPermTable[64] = { 57, 49, 41, 33, 25, 17, 9, 1,
                        	 59, 51, 43, 35, 27, 19, 11, 3,
                        	 61, 53, 45, 37, 29, 21, 13, 5,
                        	 63, 55, 47, 39, 31, 23, 15, 7,
                        	 56, 48, 40, 32, 24, 16, 8, 0,
                        	 58, 50, 42, 34, 26, 18, 10, 2,
                        	 60, 52, 44, 36, 28, 20, 12, 4,
                        	 62, 54, 46, 38, 30, 22, 14, 6 };
                        	 
int subKeyPermTable[48] = { 14, 17, 11, 24, 1, 5, 
							3, 28, 15, 6, 21, 10,
						 	23, 19, 12, 4, 26, 8,
							16, 7, 27, 20, 13, 2,
							41, 52, 31, 37, 47, 55,
							30, 40, 51, 45, 33, 48,
							44, 49, 39, 56, 34, 53,
							46, 42, 50, 36, 29, 32 };
                        
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

void leftShiftVector(vector<bool>&a) {
	
	bool temp = a[0];
	
	for (int i = 0; i < a.size(); i++) {
		
		a[i] = a[i+1];
		
		if (i == a.size() - 1) {
			
			a[a.size()-1] = temp;
			
		}
		
	}	
	
}

string boolVecToString(vector<bool> x) {
	
	string z = "";
	
	for (int i = 0; i < x.size(); i++) {
		
		if (x[i] == true) {
			
			z += "1";
			
		}else {
			
			z += "0";
			
		}
			
	}
	
	return z;
}

string stringToBinary(string x) {
    
    string y = "";
    
    for (size_t i = 0; i < x.size(); i++) {
        
        //prints 8 bits binary representation of each character of the string.
        y += bitset<8>(x.c_str()[i]).to_string();
        
    }
    
    //Returns a string of the binary representation.
    //In c++, since strings can be treated as an array,
    //this seems like a suitable choice.
    return y;
}

void insertBinaryVector(string y, vector<bool> &z) {
    
    for (int i = 0; i < y.size(); i++) {

        if (y[i] == '0') {
            
            z.push_back(false);
            
        } else {
            
            z.push_back(true);
            
        }
        
    }
    
}

//In the initial permutation, the 64 bit key we had will now be reduced to 56 bits.
//This is the initial 56-bit key.
vector<bool> initialPermutation(vector<bool> x) {
	
	string z = boolVecToString(x);
	
/*	cout << "Bool Vector put back into a string: " << endl;
	for (int j = 0; j < 64; j++) {
		
		cout << z[j];
		
		if ((j+1) % 8 == 0) {
			cout << endl;
		}
		
	} 
	cout << endl; */
	
    //Original vector size is 64.
    //This new vector<bool> y will contain 56 bits (elements).
    vector<bool> y;
    
    for (int i = 0; i < 56; i++) {
    	
    	if ( (z[initialPermTable[i]]) == '1') {
    		
    		y.push_back(true);
    		
		} else {
			
			y.push_back(false);
			
		} 	
    	
	}
        
    return y;
}

//This function simply takes in the 56 bit key and produces
//the new bool vector so we can permute it and save it as
//another vector bool.
vector<bool> newShiftedVector(vector<bool> x) {
	
	//Take the permutated 56-bit vector, and split it in half
	//Then perform a left shift on both containers.
	//Put the entire string back together
	//And the 48 bit subkey will be a permutation from the
	//subkey table
	
	vector<bool> a; //Contains first 28 elements.
	vector<bool> b; //Contains last 28 elements.
	
	//Fill the arrays with these elements.
	for (int i = 0; i < 56; i++) {
		
		if (i < 28) {
			
			a.push_back(x[i]);
			
		} else {
			
			b.push_back(x[i]);
			
		}
				
	}
	/*
	cout << "First 28 bits of the 56-bit key: ";
	for (int j = 0; j < 28; j++) cout << a[j];
	cout << endl;
	cout << endl;
	
	cout << "Last 28 bits of the 56-bit key: ";
	for (int j = 0; j < 28; j++) cout << b[j];
	cout << endl;
	cout << endl; */
	
	leftShiftVector(a);
	leftShiftVector(b);
	/*
	cout << "Shifted left First 28 bits of the 56-bit key: ";
	for (size_t j = 0; j < a.size(); j++) cout << a[j];
	cout << endl;
	cout << endl;
	
	cout << "Shifted 28 Last 28 bits of the 56-bit key: ";
	for (size_t j = 0; j < b.size(); j++) cout << b[j];
	cout << endl;
	cout << endl;  */
	
	vector<bool> mergedVector;

	for (int k = 0; k < 28; k++) {	
			
		mergedVector.push_back(a[k]);
		
	}
	
	for (int k = 0; k < 28; k++) {
		
		mergedVector.push_back(b[k]);
		
	}
	
	//Merged vector has 56 bits (post-shift) now in
	//otherPermutations we call this vector
	//and create a subkey of 48 bits based off the global var.
	return mergedVector;
}

vector<bool> subKeyPermutations(string x) {
	
//	string z = boolVecToString(x);
	vector<bool> a;
	
	for (int i = 0; i < 48; i++) {
    	
    	if ( (x[subKeyPermTable[i] - 1]) == '1') {
    		
    		a.push_back(true);
    		
		} else {
			
			a.push_back(false);
			
		} 	
    	
	}
	
	return a;
	
}

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
//  cout << "newBinaryKey " << newBinaryKey << endl;
    
    //Initial key should have 64 bits inside.
    vector<bool> initial64KeyVector;
    
    insertBinaryVector(newBinaryKey, initial64KeyVector);
    
    cout << endl << "Original 64-bit key: ";
    
    for (int i = 0; i < initial64KeyVector.size(); i++) {
        
        cout << initial64KeyVector[i];
        
    }
    cout << endl;
	cout << endl;
	
	//firstPermutatedVec now contains 56 bits of data.
	vector<bool> initial56KeyVector = initialPermutation(initial64KeyVector);  
	
/*	cout << "First 56-bit key: " << endl;
	for (int j = 0; j < 56; j++) {
		
		cout << initial56KeyVector[j];
		
		if ((j+1) % 8 == 0) {
			cout << endl;
		}
		
		
	}
	cout << endl;
	cout << endl; */
	
	vector<vector<bool>> listOfSubkeys;
	int rounds = 1;
	
	vector<bool> shiftedsubKeybeforePerm = newShiftedVector(initial56KeyVector);
	
	string SubKeyStringbeforePerm = boolVecToString(shiftedsubKeybeforePerm);
	cout << "Merged 56-bit key used to get Subkey 1: " << SubKeyStringbeforePerm << endl << endl;

	vector<bool> subKey = subKeyPermutations(SubKeyStringbeforePerm);
	
//	printArray(subKey);
//	string s = boolVecToString(secondSubKey);
//	cout << s << endl;

	listOfSubkeys.push_back(subKey);
	
	shiftedsubKeybeforePerm = newShiftedVector(shiftedsubKeybeforePerm);
	
	while (rounds < 16) {
		
		SubKeyStringbeforePerm = boolVecToString(shiftedsubKeybeforePerm);
		
		subKey = subKeyPermutations(SubKeyStringbeforePerm);
		
		listOfSubkeys.push_back(subKey);
		
		shiftedsubKeybeforePerm = newShiftedVector(shiftedsubKeybeforePerm);
		rounds++;
	}
	
	cout << "List of Subkeys: " << endl;
	print2dBoolVec(listOfSubkeys);
      
    return 0;
}

