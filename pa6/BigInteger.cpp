/***
 * Isabella Phung
 * itphung
 * 2023 Fall CSE 101 PA6
 * BigIntegerTest.cpp
 * Implementation for BigInteger ADT
 ***/

#include<stdexcept>
#include "BigInteger.h"
#include<cmath>
#include<algorithm>

const int power = 9;
const int base = pow(10, power);

// BigInteger()
// Constructor that creates a new BigInteger in the zero state: 
// signum=0, digits=().
BigInteger::BigInteger(){
    //List digits;
    signum = 0;
}

// BigInteger()
// Constructor that creates a new BigInteger from the long value x.
BigInteger::BigInteger(long x){
    if(x==0){
        signum = 0;
        return;
    }

    if (x < 0){
        signum = -1;
    }else{
        signum = 1;
    }
    long value;
    while(x != 0){
        value = x%base;
        digits.insertBefore(value); 
        x = x/base;
    }
}

void stringToList(std::string s, List& L){
    std::string substring; 
    while(s.length() > 0){
       if(s.length() > power){
            substring = s.substr(s.length()-power);
            s = s.substr(0, s.length()-power);
        }else{
            substring = s;
            s = "";
        }
        const char* charString;
        char* endptr;
        long value;

        charString = substring.c_str();
        value = strtol(charString, &endptr, 10);
        if (endptr == charString) {
            throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
        } else if (*endptr != '\0') {
            throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
        } else {
            L.insertBefore(value); 
        }
    }
    
    //removing 0s at front
    L.moveBack();
    while(L.movePrev() == 0 && L.position() != 0){
        L.eraseAfter();
    }

}

// BigInteger()
// Constructor that creates a new BigInteger from the string s.
// Pre: s is a non-empty string consisting of (at least one) base 10 digit
// {0,1,2,3,4,5,6,7,8,9}, and an optional sign {+,-} prefix.
BigInteger::BigInteger(std::string s){
    if(s.length()==0){
        throw std::invalid_argument("BigInteger: Constructor: empty string");
    }
    if(s.at(0) == '-'){
        signum = -1;
        s = s.substr(1, s.length()-1);//remove first character in string
    }else{
        if(s.at(0) == '+'){
            s = s.substr(1, s.length()-1);//remove first character in string
        }
        signum = 1;
    }
    //check if non numeric characters
    if(!std::all_of(s.begin(), s.end(), ::isdigit)){
        throw std::invalid_argument("BigInteger: Constructor: non numeric string");
    }
    stringToList(s, digits);

}

// BigInteger()
// Constructor that creates a copy of N.
BigInteger::BigInteger(const BigInteger& N){
   signum = N.signum;
   digits = List(N.digits);
}

// Optional Destuctor
// ~BigInteger()
// ~BigInteger();

// Helper functions --------------------------------------------------------

// negateList() 
// Changes the sign of each integer in List L. Used by sub(). 
void negateList(List& L){
    L.moveFront();
    long value;
    for(int i = 0; i < L.length();i++){
       value = L.moveNext();
       L.setBefore(-1*value); 
   }
}
 
// sumList() 
// Overwrites the state of S with A + sgn*B (considered as vectors). 
// Used by both sum() and sub(). 
void sumList(List& S, List A, List B, int sgn){
    A.moveFront();
    B.moveFront();
    long valueA;
    long valueB;
    S.clear();
    while(A.position() != A.length() && B.position() != B.length()){ 
        valueA = A.moveNext();
        valueB = B.moveNext();
        S.insertBefore(valueA + sgn*valueB); 
    }

    long value;
    while(A.position() != A.length()){
        value = A.moveNext();
        S.insertBefore(value);
    }
    
    while(B.position() != B.length()){
        value = sgn*B.moveNext();
        S.insertBefore(value);
    }
    
    //erasing 0s at front
    S.moveBack();
    while(S.movePrev() == 0 && S.position() != 0){
        S.eraseAfter();
    }
}
 
// normalizeList() 
// Performs carries from right to left (least to most significant  
// digits), then returns the sign of the resulting integer. Used  
// by add(), sub() and mult(). 
int normalizeList(List& L){
    L.moveFront();
    int carry=0;
    long value;
    int returnVal = 1;
    if(L.back() < 0){
        negateList(L);
        returnVal = -1;
    }
    int length = L.length();
    L.moveFront();
    for(int i = 0; i<length;i++){
        value = L.moveNext();
        if(value < 0){//negative normalization
            value = base + value;
            L.setBefore(value + carry); 
            carry = -1;
        }else{//positive normalization
            L.setBefore((value+carry) % base);
            carry = (value+carry) / base; 
            if(L.peekPrev() == L.back() && carry > 0){//if at end of list, create node for list
                L.insertAfter(carry);
            }
        }
    }
    return returnVal;
}



// shiftList() 
// Prepends p zero digits to L, multiplying L by base^p. Used by mult(). 
void shiftList(List& L, int p){
    L.moveFront();
    for(int i = 0; i < p; i++){
        L.insertBefore(0);
    }
}
 
// scalarMultList() 
// Multiplies L (considered as a vector) by m. Used mult(). 
void scalarMultList(List& L, ListElement m){
    L.moveFront();
    long value;
    for(int i = 0; i < L.length();i++){
        value = m*L.moveNext();
        L.setBefore(value);
    }
}

// Access functions --------------------------------------------------------

// sign()
// Returns -1, 1 or 0 according to whether this BigInteger is positive, 
// negative or 0, respectively.
int BigInteger::sign() const{
    return signum;
}

// compare()
// Returns -1, 1 or 0 according to whether this BigInteger is less than N,
// greater than N or equal to N, respectively.
int BigInteger::compare(const BigInteger& N) const{
    if(signum < N.signum){
        return -1;
    }
    if(N.signum < signum){
        return 1;
    }
    if(N.signum == 0 && signum == 0){
        return 0;
    }
    //if both pos, and A has less digits than B, A > B
    if(signum > 0 && N.signum > 0 && digits.length() < N.digits.length()){
        return -1;
    }

    //if both pos, and A has more digits than B, B > A
    if(signum > 0 && N.signum > 0 && digits.length() > N.digits.length()){
        return 1;
    }

    //if both neg, and A has more digits than B, A < B
    if(signum < 0 && N.signum < 0 && digits.length() < N.digits.length()){
        return 1;
    }

    //if both neg, and A has less digits than B, B < A
    if(signum < 0 && N.signum < 0 && digits.length() > N.digits.length()){
        return -1;
    }

    //signums must be equivalent @ this point, both not 0, and of same length
    List A = digits;
    List B = N.digits;
    long Aval;
    long Bval;
    A.moveBack();
    B.moveBack();
    while(A.peekPrev() != A.front()){
        Aval = A.movePrev();
        Bval = B.movePrev();
        if(Aval < Bval){
            return -1;
        }
        if(Bval < Aval){
            return 1;
        }
    }
    return 0;
}

// Manipulation procedures -------------------------------------------------

// makeZero()
// Re-sets this BigInteger to the zero state.
void BigInteger::makeZero(){
    signum = 0;
    digits.clear();
}

// negate()
// If this BigInteger is zero, does nothing, otherwise reverses the sign of 
// this BigInteger positive <--> negative. 
void BigInteger::negate(){
    signum = signum*-1;
}


// BigInteger Arithmetic operations ----------------------------------------

// add()
// Returns a BigInteger representing the sum of this and N.
BigInteger BigInteger::add(const BigInteger& N) const{
    BigInteger sum;

    if(N.signum == 0){ // if N is 0
        sum = *this;
        return sum;
    }

    if(signum == 0){ // if this is 0
        sum = N;
        return sum;
    }
   
    BigInteger Ncopy = BigInteger(N);
    Ncopy.negate();
    if(compare(Ncopy) == 0){ // if total = 0
        sum.signum = 0;
        return sum;
    }

    if(signum == 1 && N.signum == -1){ // + + - == + - +
        sumList(sum.digits, digits, N.digits, -1);
        sum.signum = normalizeList(sum.digits);
    } else if(signum == -1 && N.signum == 1){// -A + +B == +B - +A
        sumList(sum.digits, N.digits, digits, -1);
        sum.signum = normalizeList(sum.digits);
    }else{
        sumList(sum.digits, digits, N.digits, 1);
        normalizeList(sum.digits);
        if(signum == 1){
            sum.signum = 1;
        }else{
            sum.signum = -1;
        }
    }
    return sum;
}

// sub()
// Returns a BigInteger representing the difference of this and N.
BigInteger BigInteger::sub(const BigInteger& N) const{
    BigInteger difference;
    if(N.signum == 0){ // if N is 0
        difference = *this;
        return difference;
    }

    if(signum == 0){ // if this is 0
        difference = N;
        difference.negate();
        return difference;
    }

    if(compare(N) == 0){ // if total = 0
        difference.signum = 0;
        return difference;
    }

    if(signum == 1 && N.signum == -1){// + - - == + + +
        sumList(difference.digits, digits, N.digits, 1);
        difference.signum = 1;
    }else if(signum == -1 && N.signum == 1){ // - - + == - + -
        sumList(difference.digits, digits, N.digits, 1);
        difference.signum = -1;
    }else if(signum == -1){// - - - == -A + +B == +B - +A
        sumList(difference.digits, N.digits, digits, -1);
        difference.signum = normalizeList(difference.digits);   
    }else{ // + - +
        sumList(difference.digits, digits, N.digits, -1);
        difference.signum = normalizeList(difference.digits);
    }
    return difference;
}

void multList(List& S, List A, List B){
    List greater = A;
    List lesser = B;
    if(B.length()> A.length()){
        greater = B;
        lesser = A;
    }
    lesser.moveFront();
    int shift = 0;
    List C;
    while(lesser.position() != lesser.length()){
        C = greater;
        scalarMultList(C, lesser.moveNext());
        shiftList(C, shift);
        sumList(S, S, C, 1);
        normalizeList(S);
        shift++;
    }
}

// mult()
// Returns a BigInteger representing the product of this and N. 
BigInteger BigInteger::mult(const BigInteger& N) const{
    BigInteger sum;
    
    if(signum == 0 || N.signum == 0){
        return sum;
    }
    multList(sum.digits, digits, N.digits); 
    if(signum != N.signum){
        sum.signum = -1;    
    }else{
        sum.signum = 1;
    }
    return sum;
}


// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this BigInteger consisting of its
// base 10 digits. If this BigInteger is negative, the returned string 
// will begin with a negative sign '-'. If this BigInteger is zero, the
// returned string will consist of the character '0' only.
std::string BigInteger::to_string(){
    std::string s = ""; 
    if(this->signum == 0){
        s = "0";
    }else{
        if(this->signum == -1){
            s += "-";
        }
        (this->digits).moveBack();
        std::string value;
        for(int i = 0; i<(this->digits).length(); i++){
            value = std::to_string(digits.movePrev());
            if(value.length()<power && i != 0){
                while(value.length()!=power){
                    value = "0" + value;
                }
            }
            s+=value;
        }
    }

    //s+="\n";
    //s+=digits.to_string();
    return s;
    
}


// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of N into stream.
std::ostream &operator<<( std::ostream &stream, BigInteger& N ){
    return stream << N.to_string();
}

// operator==()
// Returns true if and only if A equals B. 
bool operator==( const BigInteger& A, const BigInteger& B ){
    return A.compare(B) == 0;
}

// operator<()
// Returns true if and only if A is less than B. 
bool operator<( const BigInteger& A, const BigInteger& B ){
    return A.compare(B) == -1;
}

// operator<=()
// Returns true if and only if A is less than or equal to B. 
bool operator<=( const BigInteger& A, const BigInteger& B ){
    return A.compare(B) == -1 || A.compare(B) == 0;
}

// operator>()
// Returns true if and only if A is greater than B. 
bool operator>( const BigInteger& A, const BigInteger& B ){
    return A.compare(B) == 1;
}

// operator>=()
// Returns true if and only if A is greater than or equal to B. 
bool operator>=( const BigInteger& A, const BigInteger& B ){
    return A.compare(B) == 1 || A.compare(B) == 0;
}

// operator+()
// Returns the sum A+B. 
BigInteger operator+( const BigInteger& A, const BigInteger& B ){
    return A.add(B); 
}

// operator+=()
// Overwrites A with the sum A+B. 
BigInteger operator+=( BigInteger& A, const BigInteger& B ){
    A = A.add(B); 
    return A;
}

// operator-()
// Returns the difference A-B. 
BigInteger operator-( const BigInteger& A, const BigInteger& B ){
   return A.sub(B); 
}

// operator-=()
// Overwrites A with the difference A-B. 
BigInteger operator-=( BigInteger& A, const BigInteger& B ){
    A = A.sub(B); 
    return A;
}

// operator*()
// Returns the product A*B. 
BigInteger operator*( const BigInteger& A, const BigInteger& B ){
    return A.mult(B);
}

// operator*=()
// Overwrites A with the product A*B. 
BigInteger operator*=( BigInteger& A, const BigInteger& B ){
    A = A.mult(B);
    return A;
}

