#include<iostream>
#include<string>
#include<stdexcept>
#include"BigInteger.h"

using namespace std;

int main(){
    BigInteger test;
    test = BigInteger("12345");
    cout<<test<<endl;
    /**
    //testing with strings, substrings and strtol
    char a[] = "abcd";
    char b[] = "ab1c2d";
    string c = "123456789";
    const char* charC = c.c_str();
    char* endptr;
    long value = strtol(charC, &endptr, 10);
    if (endptr == charC) {
        printf("No digits were found\n");
    } else if (*endptr != '\0') {
        printf("Invalid input: %s\n", charC);
    } else {
        printf("The value is %ld\n", value);
    }
    string test = c.substr(0, 4);
    cout << test << endl; 
    **/
    return 0;
}

