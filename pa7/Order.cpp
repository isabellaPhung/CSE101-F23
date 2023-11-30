/***
 * Isabella Phung
 * itphung
 * 2023 Fall CSE 101 PA7
 * Order.cpp
 * Client program for Dictionary ADT. Reads file 
 * and places lines alphabetically in a Dictionary with line numbers.
 ***/

#include<iostream>
#include<fstream>
#include<string>
#include"Dictionary.h"

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
    
   Dictionary A;
   int linenum = 0;
   while(getline(in, line)){
        linenum++; 
        A.setValue(line, linenum);
   }
   out<<A<<endl;
   out<<A.pre_string()<<endl;

// close files 
   in.close();
   out.close();

   return(EXIT_SUCCESS);
}

