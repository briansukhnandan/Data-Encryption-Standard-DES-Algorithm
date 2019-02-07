#include <iostream>
#include <string>
#include <vector>
#include <bitset>
using namespace std;

//Global variables for DES initial permutation
int initialPerm[64] = { 57, 49, 41, 33, 25, 17, 9, 1,
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

string stringToBinary(string x) {
    
    string y = "";
    
    for (size_t i = 0; i < x.size(); i++) {
        
        //prints 8 bits binary representation of each character of the string.
        y += bitset<8>(x.c_str()[i]).to_string();
        
    }
    
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

void initialPermutation(vector<int> x) {
    
    
    
    
}

//Key we're working with: IEOFIT#1
//In binary this is : which is 64 bits long.
//01001001 01000101 01001111 01000110 
//01001001 01010100 00100011 00110001

int main() {
    
    string stringKey = "IEOFIT#1";
    
    string newBinaryKey = stringToBinary(stringKey);
    cout << "newBinaryKey " << newBinaryKey << endl;
    //Initial key should have 64 bits inside.
    vector<bool> initialKeyVector;
    
    insertBinaryVector(newBinaryKey, initialKeyVector);
    
    cout << "Vector of bool values: ";
    
    for (int i = 0; i < initialKeyVector.size(); i++) {
        
        cout << initialKeyVector[i];
        
    }
      
      
    return 0;
}

