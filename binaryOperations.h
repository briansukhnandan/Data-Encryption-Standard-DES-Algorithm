#include <bitset>
#include <string>
#include <vector>

std::string stringToBinary(std::string x) {
    
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

void insertBinaryVector(std::string y, std::vector<bool> &z) {
    
    for (int i = 0; i < y.size(); i++) {

        if (y[i] == '0') {
            
            z.push_back(false);
            
        } else {
            
            z.push_back(true);
            
        }
        
    }
    
}


