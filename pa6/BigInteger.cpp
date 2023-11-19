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
    signum = 0;
    List digits;
}

// BigInteger()
// Constructor that creates a new BigInteger from the long value x.
BigInteger::BigInteger(long x){
    List digits;
    if(x==0){
        signum = 0;
        return;
    }

    if (x < 0){
        signum = -1;
    }else{
        signum = 1;
    }
    long value = 1;
    while(value != 0){
        value = x%base;
        digits.insertBefore(value); 
        x = x/base;
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
    }else{
        signum = 1;
    }
    s = s.substr(1, s.length()-1);//remove first character in string
    //check if non numeric characters
    if(!std::all_of(s.begin(), s.end(), ::isdigit)){
        throw std::invalid_argument("BigInteger: Constructor: non numeric string");
    }

    int substrings = s.length()/power + 1;
    std::string substring = "";
    const char* charString;
    char* endptr;
    long value;
    for(int i = 0; i < substrings; i++){
        substring = s.substr(s.length()-1-power);
        s = s.substr(0, s.length()-1-power);
        charString = substring.c_str();
        value = strtol(charString, &endptr, 10);
        if (endptr == charString) {
            throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
        } else if (*endptr != '\0') {
            throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
        } else {
            digits.insertBefore(value); 
        }
    }
}

// BigInteger()
// Constructor that creates a copy of N.
BigInteger::BigInteger(const BigInteger& N){
   signum = N.signum;
   List digits = N.digits;
}

// Optional Destuctor
// ~BigInteger()
// ~BigInteger();

// Helper functions --------------------------------------------------------

// negateList() 
// Changes the sign of each integer in List L. Used by sub(). 
void negateList(List& L){
    L.moveFront();
    for(int i = 0; i < L.length();i++){
       L.setAfter(-1*L.moveNext()); 
   }
}
 
// sumList() 
// Overwrites the state of S with A + sgn*B (considered as vectors). 
// Used by both sum() and sub(). 
void sumList(List& S, List A, List B, int sgn){
    S.clear();
    A.moveFront();
    B.moveFront();
    while(A.peekPrev() != A.back() && B.peekPrev() != B.back()){ 
       S.insertBefore(A.moveNext() + sgn*B.moveNext()); 
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
    if(L.front() < 0){
        negateList(L);
        returnVal = -1;
    }
    for(int i = 0; i<L.length();i++){
        value = L.moveNext();
        if(value < 0){//negative normalization
            if(abs(value) >= base){
                value = base - value;
                carry = -1;
                L.setBefore(L.peekPrev()+carry); 
            }
        }else{//positive normalization
            carry = value / base; 
            if(value >= base){
                L.setBefore(value % base);
                if(L.peekNext() == L.back()){//if at end of list, create node for list
                    L.insertBefore(carry);
                }else{
                    L.setBefore(L.peekPrev()+carry);
                }
            }
        }
    }
    return returnVal;
}
 
// shiftList() 
// Prepends p zero digits to L, multiplying L by base^p. Used by mult(). 
void shiftList(List& L, int p){
    L.moveFront();
    std::string s = "";
    //create string from List L
    while(L.peekNext() != L.back()){
        s=std::to_string(L.moveNext()) + s;
    }
    //append 0s to it
    for(int i = 0; i<p; i++){
        s+= "0";
    }
    //convert back to list
    L.clear();
    int substrings = s.length()/power + 1;
    std::string substring = "";
    const char* charString;
    char* endptr;
    long value;
    for(int i = 0; i < substrings; i++){
        substring = s.substr(s.length()-1-power);
        s = s.substr(0, s.length()-1-power);
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

}
 
// scalarMultList() 
// Multiplies L (considered as a vector) by m. Used by mult(). 
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
    if(signum < N.signum || digits.length() < N.digits.length()){
        return -1;
    }
    if(N.signum < signum || N.digits.length() < digits.length()){
        return 1;
    }
    if(N.signum == 0 && signum == 0){
        return 0;
    }
    //signums must be equivalent @ this point, both not 0, and of same length
    List A = digits;
    List B = N.digits;
    long Aval;
    long Bval;
    A.moveBack();
    B.moveBack();
    while(A.peekNext() != A.front()){
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
    sumList(sum.digits, digits, N.digits, 1);
    normalizeList(sum.digits);
    //TODO figure out how to do signum
    return sum;
}

// sub()
// Returns a BigInteger representing the difference of this and N.
BigInteger BigInteger::sub(const BigInteger& N) const{
    BigInteger difference;
    sumList(difference.digits, digits, N.digits, -1);
    normalizeList(difference.digits);
    //TODO figure out how to do signum
    return difference;
}

void multList(List& S, List A, List B){
    A.moveFront();
    while(A.peekPrev() != A.back()){
        scalarMultList(B, A.moveNext());
        sumList(S, S, B, 1);
        normalizeList(S);
    }
}

// mult()
// Returns a BigInteger representing the product of this and N. 
BigInteger BigInteger::mult(const BigInteger& N) const{
    BigInteger sum;
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
    if(signum == 0){
        s = "0";
    }else{
        if(signum == -1){
            s += "-";
        }
        digits.moveBack();
        for(int i = 0; i<digits.length(); i++){
            s+=std::to_string(digits.movePrev());
        }
    }
    return s;
    
}


// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of N into stream.
std::ostream& operator<<( std::ostream& stream, BigInteger N ){
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

