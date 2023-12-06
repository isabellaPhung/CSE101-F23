Isabella Phung
1702285
Fall 2023
pa8
CSE101
____________
Description:
Program contains Dictionary.cpp, Dictionary.h, DictionaryTest.h, Order.cpp, WordFrequency.cpp, and the Makefile
Contains library of functions for the Dictionary ADT. Order.cpp is a client program that utilizes the Dictionary ADT to create Dictionaries from file inputs and uses the provided functions to display the dictionary. WordFrequency.cpp is another client program that utilizes the same ADT to count the frequency words appear in an inputted text file.
_____________
Files:
WordFrequency.cpp - main program. Can be opened in any C editor or compiled using gcc with the provided Makefile. Accepts two file names for the input and output files.
Order.cpp - main program. Can be opened in any C editor or compiled using gcc with the provided Makefile. Accepts two file names for the input and output files.
Dictionary.h - header file for Dictionary.cpp
Dictionary.cpp - implementation of the Dictionary ADT library.
DictionaryTest.cpp - tester file for the Dictionary ADT library
Makefile - compiles WordFrequency, Order.cpp, Dictionary.cpp, and DictionaryTest.cpp. Use via "make" command. Can also perform "make clean" which will remove any object files in the folder and "make format" which will format the .cpp files.
Run code by entering directory and typing "make" command, then typing ./WordFrequency [input filepath] [output filepath] or ./Order [input filepath] [output filepath]
