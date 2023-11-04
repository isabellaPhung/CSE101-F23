Isabella Phung
1702285
Fall 2023
pa4
CSE101
____________
Description:
Program contains List.c, List.h, Matrix.c, Matrix.h, MatrixTest.c, ListTest.c, and Sparse.c 
Contains library of functions for the Matrix ADT which uses List ADTs. Sparse.c is a client program that utilizes the Matrix ADT to create matricies from file inputs and uses functions in Matrix.c to perform matrix arithmetic.
_____________
Files:
Sparse.c - main program. Can be opened in any C editor or compiled using gcc with the provided Makefile. Accepts two file names for the input and output files.
List.h - header file for List.c
List.c - implementation of the List ADT library. Now accepts all datatypes
ListTest.c - tester file for the List ADT library
Matrix.h - header file for Matrix.c
Matrix.c - implementation of the Matrix ADT library
MatrixTest.c - tester file for the Matrix ADT library
Makefile - compiles List.c, Matrix.c, MatrixTest.c, ListTest.c, and Sparse.c. Use via "make" command. Can also perform "make clean" which will remove any object files in the folder and "make format" which will format the .c files according to clang-15's format specifications.
Run code by entering directory and typing "make" command, then typing ./Sparse [input filepath] [output filepath]

input files should be in the following format:
[size of square matrix] [non-zero elements in Matrix A] [non-zero elements in Matrix B]

[row] [col] [data for Matrix A]
...

[row] [col] [data for Matrix B]
...

The Graph ADT has the following functions for accessing and manipulating the ADT:

// newMatrix() 
// Returns a reference to a new nXn Matrix object in the zero state. 
Matrix newMatrix(int n) 
 
// freeMatrix() 
// Frees heap memory associated with \*pM, sets \*pM to NULL. 
void freeMatrix(Matrix\* pM); 
 
// Access functions  
 
// size() 
// Return the size of square Matrix M. 
int size(Matrix M); 
 
// NNZ() 
// Return the number of non-zero elements in M. 
int NNZ(Matrix M); 
 
// equals() 
// Return true (1) if matrices A and B are equal, false (0) otherwise. 
int equals(Matrix A, Matrix B); 
 
 
// Manipulation procedures  
 
// makeZero() 
// Re-sets M to the zero Matrix state. 
void makeZero(Matrix M); 
 
// changeEntry() 
// Changes the ith row, jth column of M to the value x. 
// Pre: 1<=i<=size(M), 1<=j<=size(M) 
void changeEntry(Matrix M, int i, int j, double x); 
 
 
// Matrix Arithmetic operations  
 
// copy() 
// Returns a reference to a new Matrix object having the same entries as A. 
Matrix copy(Matrix A); 
 
// transpose() 
// Returns a reference to a new Matrix object representing the transpose 
// of A. 
Matrix transpose(Matrix A); 
 
// scalarMult() 
// Returns a reference to a new Matrix object representing xA. 
Matrix scalarMult(double x, Matrix A); 
 
// sum() 
// Returns a reference to a new Matrix object representing A+B. 
// pre: size(A)==size(B) 
Matrix sum(Matrix A, Matrix B); 
 
// diff() 
// Returns a reference to a new Matrix object representing A-B. 
// pre: size(A)==size(B) 
Matrix diff(Matrix A, Matrix B); 
 
// product() 
// Returns a reference to a new Matrix object representing AB 
// pre: size(A)==size(B) 
Matrix product(Matrix A, Matrix B); 
 
// printMatrix() 
// Prints a string representation of Matrix M to filestream out. Zero rows  
// are not printed.  Each non-zero row is represented as one line consisting  
// of the row number, followed by a colon, a space, then a space separated  
// list of pairs "(col, val)" giving the column numbers and non-zero values  
// in that row. The double val will be rounded to 1 decimal point. 
void printMatrix(FILE\* out, Matrix M);
