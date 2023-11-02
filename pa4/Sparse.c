/***
 * Isabella Phung
 * itphung
 * 2023 Fall CSE 101 PA3
 * Sparse.c
 * Client program for Matrix ADT
 ***/

#include "Matrix.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  if (argc != 3) {
    fprintf(stderr, "Less than two command line arguments given! Please "
                    "provide input file and output file.\n");
    exit(EXIT_FAILURE);
  }
  FILE *input = fopen(argv[1], "r");
  FILE *output = fopen(argv[2], "w");
  if (input == NULL) {
    fprintf(stderr, "Could not open %s.\n", argv[1]);
    fclose(output);
    exit(EXIT_FAILURE);
  }
  
  int n;
  int a;
  int b;
  fscanf(input, "%d %d %d", &n, &a, &b);
  //fill in matrix A
  A = newMatrix();
  for(int i = 0; i< a; i++){
    fscanf(input, "%d %d %d", &row, &column, &data);
    changeEntry(A, row, column, data);
  }
  B = newMatrix();
  //fill in matrix B 
  for(int i = 0; i< b; i++){
    fscanf(input, "%d %d %d", &row, &column, &data);
    changeEntry(B, row, column, data);
  }

  fclose(input);
  fclose(output);
  return 0;
}

