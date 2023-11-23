/***
 * Isabella Phung
 * itphung
 * 2023 Fall CSE 101 PA6
 * Arithmetic.cpp
 * Client program for BigInteger ADT. Reads file for
 * big integers and performs some calculations with them.
 ***/

#include<iostream>
#include<fstream>
#include<string>
#include"BigInteger.h"

using namespace std;

int main(int argc, char * argv[]){
   ifstream in;
   ofstream out;
   string line;

   // check command line for correct number of arguments
   if( argc != 3 ){
      cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
      return(EXIT_FAILURE);
   }

   // open files for reading and writing 
   in.open(argv[1]);
   if( !in.is_open() ){
      cerr << "Unable to open file " << argv[1] << " for reading" << endl;
      return(EXIT_FAILURE);
   }

   out.open(argv[2]);
   if( !out.is_open() ){
      cerr << "Unable to open file " << argv[2] << " for writing" << endl;
      return(EXIT_FAILURE);
   }

   getline(in, line);
   BigInteger A = BigInteger(line);
   getline(in, line);
   getline(in, line);
   BigInteger B = BigInteger(line);
   BigInteger test;
   
   out << A << endl << endl;
   out << B << endl << endl;
  
   test = A+B;
   out << test << endl << endl;

   test = A-B;
   out << test << endl << endl;

   test = A-A;
   out << test << endl << endl;
   
   test = BigInteger(3)* A;
   BigInteger test2  = BigInteger(2)* B;
   test -= test2;
   out << test << endl << endl;

   test = A*B;
   out << test << endl << endl;

   test = A*A;
   out << test << endl << endl;

   test = B*B;
   out << test << endl << endl;
   
   test = A*A;
   test *= A; 
   test *= A; 
   test *= BigInteger(9);
   
   test2 = B*B;
   test2 *= B; 
   test2 *= B; 
   test2 *= B; 
   test2 *= BigInteger(16);

   test += test2;
   out << test << endl << endl;
   //out << scalarMult(9, A*A*A*A)+scalarMult(16, B*B*B*B*B);

   // close files 
   in.close();
   out.close();

   return(EXIT_SUCCESS);
}

