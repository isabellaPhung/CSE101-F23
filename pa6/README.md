Isabella Phung
1702285
Fall 2023
pa6
CSE101
____________
Description:
Program contains List.cpp, List.h, ListTest.h, Arithmetic.cpp, Makefile,  BigInteger.h, BigInteger.cpp, and BigIntegerTest.cpp 
Contains library of functions for the BigInteger ADT which uses List ADTs. Arithmetic.cpp is a client program that utilizes the BigInteger ADT to create BigIntegers from file inputs and uses functions in BigInteger.cpp to perform basic arithmetic.
_____________
Files:
Arithmetic.cpp - main program. Can be opened in any C editor or compiled using gcc with the provided Makefile. Accepts two file names for the input and output files.
List.h - header file for List.c
List.cpp - implementation of the List ADT library. Now accepts longs.
ListTest.cpp - tester file for the List ADT library
BigInteger.h - header file for BigInteger.cpp
BigInteger.cpp - implementation of the BigInteger ADT library
BigIntegerTest.cpp - tester file for the BigInteger ADT library
Makefile - compiles List.cpp, BigInteger.cpp, BigIntegerTest.cpp, ListTest.cpp, and Sparse.cpp. Use via "make" command. Can also perform "make clean" which will remove any object files in the folder and "make format" which will format the .cpp files.
Run code by entering directory and typing "make" command, then typing ./Arithmetic [input filepath] [output filepath]

input files should be in the following format:
[first BigInteger]
[newline]
[second BigInteger]

Arithmetic will perform the following computations:
𝐴, 𝐵, 𝐴+𝐵, 𝐴−𝐵, 𝐴−𝐴, 3𝐴−2𝐵, 𝐴𝐵, 𝐴^2, 𝐵^2, 9𝐴^4 +16𝐵^5
