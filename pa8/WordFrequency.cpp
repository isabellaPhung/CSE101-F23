/***
 * Isabella Phung
 * itphung
 * 2023 Fall CSE 101 PA8
 * WordFrequency.cpp
 * Client program for Dictionary ADT. Reads file 
 * and counts frequency of word appearence.
 ***/

#include<iostream>
#include<fstream>
#include<string>
#include"Dictionary.h"

using namespace std;

#define MAX_LEN 300

int main(int argc, char * argv[]){
   size_t begin, end, len;
   ifstream in;
   ofstream out;
   string line;
   string token;
   string delim = " \t\\\"\',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789";

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

   // read each line of input file, then count and print tokens 
   Dictionary A;
   int val;
   while( getline(in, line) )  {
      len = line.length();

      // get first token
      begin = min(line.find_first_not_of(delim, 0), len);
      end   = min(line.find_first_of(delim, begin), len);
      token = line.substr(begin, end-begin);
           
      while( token!="" ){  // we have a token
        for (char &c : token) { 
            c = std::tolower(c); 
        } 
        //cout<<token<<endl;

        if(A.contains(token)){
            val = A.getValue(token); 
            val++;
            //printf("val: %d\n", val);
            A.setValue(token, val);
         }else{
            A.setValue(token, 1);
         }

         // get next token
         begin = min(line.find_first_not_of(delim, end+1), len);
         end   = min(line.find_first_of(delim, begin), len);
         token = line.substr(begin, end-begin);
      }
   }
  out<<A<<endl;
  //out<<A.pre_string()<<endl;

   // close files 
   in.close();
   out.close();

   return(EXIT_SUCCESS);
}
