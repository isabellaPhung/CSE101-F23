/***
 * Isabella Phung
 * itphung
 * 2023 Fall CSE 101 PA8
 * DictionaryTest.cpp
 * Tester file for Dictionary ADT
 ***/

#include<iostream>
#include<string>
#include<stdexcept>
#include"Dictionary.h"

using namespace std;

int main(){
    Dictionary A;
    printf("Dictionary A:\n");
    A.setValue("uh", 1);

    A.setValue("test", 2);
    cout << A << endl;
    //cout << endl;
    A.setValue("uh", 3);
    cout << A << endl;
    //cout << endl;
    A.setValue("gweh", 4);
    A.setValue("mleh", 1);
    A.setValue("eugh", 10);
    A.setValue("guh", 9);
    A.setValue("geh", 8);
    A.setValue("whee", 7);
    A.setValue("whup", 6);
    A.setValue("eunguh", 5);
    A.setValue("rugh", 100);
    cout << A.pre_string() << endl;
    printf("A size: %d\n", A.size());
    cout << endl;

    //contains test
    if(A.contains("whee")){
        printf("A contains whee\n");
    }
    if(!A.contains("bleh")){
        printf("A does not contain bleh\n");
    }
    cout << endl;

    //copy test
    printf("Dictionary B:\n");
    Dictionary B = A;
    cout << B << endl;
    printf("B size: %d\n", B.size());
    cout << endl;

    //contains test
    if(B.contains("whee")){
        printf("B contains whee\n");
    }
    if(!B.contains("bleh")){
        printf("B does not contain bleh\n");
    }
    cout << endl;

    //equals test
    if(A == B){
        printf("A equals B\n");
    }
    cout << endl;
    
    //remove test
    B.remove("guh");
    //B.remove("duh");
    cout << B << endl;
    printf("B size: %d\n", B.size());

    //equals test
    if(!(A == B)){
        printf("A does not equal B\n");
    }

    //getValue test
    printf("whee's value in B is: %d\n", B.getValue("whee"));
    A.setValue("whee", 227);
    printf("whee's value in A is: %d\n", A.getValue("whee"));
    //printf("duh's value is: %d\n", B.getValue("duh"));
    cout << endl;

    //cursor tests
    if(!A.hasCurrent()){
        printf("A does not have a defined current\n");
    }
    A.begin();
    if(A.hasCurrent()){
        printf("A has a defined current\n");
    }
    cout<<A.currentKey() + " : " + std::to_string(A.currentVal()) <<endl;
    A.prev();
    if(!A.hasCurrent()){
        printf("A does not have a defined current\n");
    }
    A.begin();
    A.next();
    cout<<A.currentKey() + " : " + std::to_string(A.currentVal()) <<endl;

    A.end();
    cout<<A.currentKey() + " : " + std::to_string(A.currentVal()) <<endl;
    A.next();
    if(!A.hasCurrent()){
        printf("A does not have a defined current\n");
    }
    return 0;
}
