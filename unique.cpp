/*******************************************************************************
 * Name        : unique.cpp
 * Author      : Lucas Vanzelli
 * Date        : 09/26/24
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <cctype>
using namespace std;

bool is_all_lowercase(const string &s) {
    for(char c : s){ //Loops through each character of s
        if(!(islower(c))){ //if the character is not lowercase
            return false; //character is not lowercase
        } 
    }
    return true; //all characters are lowercase
    }


bool all_unique_letters(const string &s) {
    unsigned int setter; //unsigned integer used to save the distance between the beginning of the alphabet and c
    unsigned int vector = 0; //unsigned 0 integer used save unique values
    for(char c : s){ //Loops through the s string
        setter = 1 << (c - 'a');  //distance between the beginning of the alphabet and c
        int slay = vector & setter; //slay holds the value of vector and setter compared with a bit-and operator
        if(slay == 0){ //if the value in setter is unique
            vector = vector | setter; //Saves that value into the setter
        } else { //else it has been saved before
            return false; //returns false since there are duplicate characters
        }
    }
    return true; //all letters are unique
}

int main(int argc, char * const argv[]) {
    //Case to check if there are no input arguments
    if(argc <= 1){
        cerr << "Usage: ./unique <string>" << endl;
        return 1;
    }

    //Case to check if there are too many input arguments (more than 1)
    if(argc > 2){
        cerr << "Usage: ./unique <string>" << endl;
        return 1;
    }

    //Case to check if the input argument characters are lowercase letters
    if(!(is_all_lowercase(argv[1]))){
        cerr << "Error: String must contain only lowercase letters." << endl;
        return 1;
    }

    //Case to check if the input argument is unique
    if(!(all_unique_letters(argv[1]))){
        cerr << "Duplicate letters found." << endl;
        return 1;
    } else {
        cout << "All letters are unique." << endl;
    }
        
}

    


