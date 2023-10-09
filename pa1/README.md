Isabella Phung
1702285
Fall 2023
pa1
CSE101
____________
Description:
Program contains List.c, List.h, Lex.c, and ListTest.c. 
Contains library of functions for the List ADT which holds integers. Lex.c is a client program that utilizes the List ADT to sort a file's lines lexicographically according to ASCII order. these lines are denoted with the \n hidden character, not by word wrap.
_____________
Files:
Lex.c - main program. Can be opened in any C editor or compiled using gcc with the provided Makefile. Accepts two file names for the input and output files.
List.h - header file for List.c
List.c - implementation of the List ADT library
ListClient.c - tester file for the List ADT library
Makefile - compiles List.c and Lex.c with additional c files. Use via "make" command. Can also perform "make clean" which will remove any object files in the folder and "make format" which will format the .c files according to clang-15's format specifications.
Run code by entering directory and typing "make" command, then typing ./Lex [input filepath] [output filepath]

