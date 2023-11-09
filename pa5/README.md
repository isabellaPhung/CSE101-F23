Isabella Phung
1702285
Fall 2023
pa5
CSE101
____________
Description:
Program contains List.cpp, List.h, ListTest.cpp, and Shuffle.cpp
Contains library of functions for the Matrix ADT which uses List ADTs. Shuffle.cpp is a client program that utilizes the List ADT to perform the riffle shuffle on a deck of user inputed deck size.
_____________
Files:
Shuffle.c - main program. Can be opened in any C editor or compiled using gcc with the provided Makefile. Accepts two file names for the input and output files.
List.h - header file for List.c
List.cpp - implementation of the List ADT library
ListTest.cpp - tester file for the List ADT library
Makefile - compiles List.cpp, ListTest.cpp, and Sparse.cpp. Use via "make" command. Can also perform "make clean" which will remove any object files in the folder and "make format" which will format the .cpp files according to clang-15's format specifications.
Run code by entering directory and typing "make" command, then typing ./Sparse [deck size]
