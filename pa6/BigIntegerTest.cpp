#include<iostream>
#include<string>
#include<stdexcept>
#include"BigInteger.h"

using namespace std;

int main(){
    BigInteger test = BigInteger("12345");
    cout<< test <<endl;
    test = BigInteger("-123456");
    cout<< test <<endl;
    long value = 123456;
    BigInteger test2 = BigInteger(value);
    cout<< test2 <<endl;
    if(test<test2){
        printf("test is less than test2\n");
    }
    if(test2>test){
        printf("test2 is greater than test\n");
    }
    test.negate();
    cout<< test <<endl;
    printf("test sign: %d\n", test.sign());
    
    if(test==test2){
        printf("negated test is equal to test2\n");
    }
    
    //test.makeZero();
    //cout<< test <<endl;
    BigInteger sum = test + test2;
    //BigInteger sum = test.add(test2);
    cout << "123456+123456=" << sum << endl;
    BigInteger test3 = BigInteger("999999");
    BigInteger test4 = BigInteger("999999");
    sum = test3 + test4;
    cout << "999999+999999="<< sum << endl;
    
    test3 = BigInteger("12345");
    test4 = BigInteger("123456");
    sum = test3 + test4;
    cout << "12345+123456="<<sum << endl;
    
    test3 = BigInteger("20000");
    cout << test3 << endl;
    
    test3 = BigInteger("12345");
    test4 = BigInteger("-45");
    sum = test3 + test4;
    cout << "12345+-45="<<sum << endl;
    
    test3 = BigInteger("12345");
    test4 = BigInteger("-12345");
    sum = test3 + test4;
    cout << "12345+-12345="<<sum << endl;
    
    test3 = BigInteger("659179");
    test4 = BigInteger("882133");
    sum = test3 - test4;
    cout << "659179-882133="<<sum << endl;

    test3 = BigInteger("-12345");
    test4 = BigInteger("45");
    sum = test3 + test4;
    cout << "-12345+45="<<sum << endl;
    
    test3 = BigInteger("90");
    test4 = BigInteger("4600");
    sum = test3 + test4;
    cout << "90+4600="<<sum << endl;

    test3 = BigInteger("12345");
    test4 = BigInteger("2");
    sum = test3*test4;
    cout << "12345*2=" <<sum << endl;

    test3 = BigInteger("12345");
    test4 = BigInteger("2");
    sum = test4*test3;
    cout << "2*12345=" <<sum << endl;

    test3 = BigInteger("12345");
    test4 = BigInteger("90");
    sum = test4*test3;
    cout << "12345*90=" <<sum << endl;
    
    test3 = BigInteger("12345");
    test4 = BigInteger("123");
    sum = test4*test3;
    cout << "12345*123=" <<sum << endl;

    test3 = BigInteger("12345");
    test4 = BigInteger("-12345");
    sum = test4*test3;
    cout << "12345*-12345=" <<sum << endl;
    
    test3 = BigInteger("-123456");
    test4 = BigInteger("-123456");
    sum = test4*test3;
    cout << "-123456*-123456=" <<sum << endl;


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

