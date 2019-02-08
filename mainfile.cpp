#include <iostream>
#include <string>
#include <vector>
#include <bitset>
using namespace std;

//Global variables for DES initial permutation
int initialPermTable[64] = { 57, 49, 41, 33, 25, 17, 9, 1,
                        	 59, 51, 43, 35, 27, 19, 11, 3,
                        	 61, 53, 45, 37, 29, 21, 13, 5,
                        	 63, 55, 47, 39, 31, 23, 15, 7,
                        	 56, 48, 40, 32, 24, 16, 8, 0,
                        	 58, 50, 42, 34, 26, 18, 10, 2,
                        	 60, 52, 44, 36, 28, 20, 12, 4,
                        	 62, 54, 46, 38, 30, 22, 14, 6 };
                        

void numberToBinary(int x) {
    
    int r;
    int y[1000];
    int elements;
    int index = 0;
    
  //  r = x % 2;
    do {
        
        r = x%2;
        
        y[index] = r;
        
        x /= 2;
        
        index++;
        
    }while (x > 0);
    
    for (int i = index - 1; i >= 0; i--) {
        
        cout << y[i]; 
        
    }
    
    
}

string boolvectoString(vector<bool> x) {
	
	string z = "";
	
	for (int i = 0; i < 64; i++) {
		
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
vector<bool> initialPermutation(vector<bool> x) {
	
	string z = boolvectoString(x);
	cout << "Bool Vector put back into a string: " << endl;
	for (int j = 0; j < 64; j++) {
		
		cout << z[j];
		
		if ((j+1) % 8 == 0) {
			cout << endl;
		}
		
	}
	cout << endl;
//	cout << "Bool Vector put back into a string: " <<  z << endl;
	
    //Original vector size is 64.
    //This new vector<bool> y will contain 56 bits (elements).
    vector<bool> y;
    
    //The 
    for (int i = 0; i < 56; i++) {
    	
    	if ( (z[initialPermTable[i]]) == '1') {
    		
    		y.push_back(true);
    		
		} else {
			
			y.push_back(false);
			
		}
    	
    	
    	
	}
    
    
    return y;
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
    cout << "newBinaryKey " << newBinaryKey << endl;
    //Initial key should have 64 bits inside.
    vector<bool> initialKeyVector;
    
    insertBinaryVector(newBinaryKey, initialKeyVector);
    
    
    cout << endl << "Vector of bool values: ";
    
    for (int i = 0; i < initialKeyVector.size(); i++) {
        
        cout << initialKeyVector[i];
        
    }
    cout << endl;
	cout << endl;
	
	vector<bool> firstPermutatedVec = initialPermutation(initialKeyVector);  
	
	cout << "First permutation key: " << endl;
	for (int j = 0; j < 64; j++) {
		
		cout << firstPermutatedVec[j];
		
		if ((j+1) % 8 == 0) {
			cout << endl;
		}
		
		
	}
	cout << endl;
      
    return 0;
}

