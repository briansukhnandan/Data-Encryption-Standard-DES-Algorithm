#include <string>
#include <vector>

#include "permutationTables.h"

void leftShiftVector(std::vector<bool>&a) {
	
	bool temp = a[0];
	
	for (int i = 0; i < a.size(); i++) {
		
		a[i] = a[i+1];
		
		if (i == a.size() - 1) {
			
			a[a.size()-1] = temp;
			
		}
		
	}	
	
}

void left2bitShiftVector(std::vector<bool>&a) {
	
	leftShiftVector(a);
	leftShiftVector(a);
	
}

std::string boolVecToString(std::vector<bool> x) {
	
	std::string z = "";
	
	for (int i = 0; i < x.size(); i++) {
		
		if (x[i] == true) {
			
			z += "1";
			
		}else {
			
			z += "0";
			
		}
			
	}
	
	return z;
}

std::vector<bool> originalKeyPermutation(std::vector<bool> x) {
	
	std::string z = boolVecToString(x);
	
    //Original vector size is 64.
    std::vector<bool> y;
    
    for (int i = 0; i < 64; i++) {
    	
    	if ( (z[bit64Permutation[i]]) == '1') {
    		
    		y.push_back(true);
    		
		} else {
			
			y.push_back(false);
			
		} 	
    	
	}
        
    return y;
}

//In the initial permutation, the 64 bit key we had will now be reduced to 56 bits.
//This is the initial 56-bit key.
std::vector<bool> initialPermutation(std::vector<bool> x) {
	
	std::string z = boolVecToString(x);
	
/*	cout << "Bool Vector put back into a std::string: " << endl;
	for (int j = 0; j < 64; j++) {
		
		cout << z[j];
		
		if ((j+1) % 8 == 0) {
			cout << endl;
		}
		
	} 
	cout << endl; */
	
    //Original vector size is 64.
    //This new std::vector<bool> y will contain 56 bits (elements).
    std::vector<bool> y;
    
    for (int i = 0; i < 56; i++) {
    	
    	if ( (z[initialPermTable[i] - 1]) == '1') {
    		
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
std::vector<bool> newShiftedVector(std::vector<bool> x) {
	
	//Take the permutated 56-bit vector, and split it in half
	//Then perform a left shift on both containers.
	//Put the entire std::string back together
	//And the 48 bit subkey will be a permutation from the
	//subkey table
	
	std::vector<bool> a; //Contains first 28 elements.
	std::vector<bool> b; //Contains last 28 elements.
	
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
	
	std::vector<bool> mergedVector;

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

std::vector<bool> new2ShiftedVector(std::vector<bool> x) {
	
	
	std::vector<bool> a; //Contains first 28 elements.
	std::vector<bool> b; //Contains last 28 elements.
	
	//Fill the arrays with these elements.
	for (int i = 0; i < 56; i++) {
		
		if (i < 28) {
			
			a.push_back(x[i]);
			
		} else {
			
			b.push_back(x[i]);
			
		}
				
	}
	
	left2bitShiftVector(a);
	left2bitShiftVector(b);
	
	std::vector<bool> mergedVector;

	for (int k = 0; k < 28; k++) {	
			
		mergedVector.push_back(a[k]);
		
	}
	
	for (int k = 0; k < 28; k++) {
		
		mergedVector.push_back(b[k]);
		
	}
	
	return mergedVector;
	
}

std::vector<bool> subKeyPermutations(std::string x) {
	
//	std::string z = boolVecTostd::string(x);
	std::vector<bool> a;
	
	for (int i = 0; i < 48; i++) {
    	
    	if ( (x[subKeyPermTable[i] - 1]) == '1') {
    		
    		a.push_back(true);
    		
		} else {
			
			a.push_back(false);
			
		} 	
    	
	}
	
	return a;
	
}
