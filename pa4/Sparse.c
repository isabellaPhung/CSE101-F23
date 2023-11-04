/***
 * Isabella Phung
 * itphung
 * 2023 Fall CSE 101 PA4
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
  int row;
  int column;
  double data;
  fscanf(input, "%d %d %d", &n, &a, &b);
  // fill in matrix A
  Matrix A = newMatrix(n);
  for (int i = 0; i < a; i++) {
    fscanf(input, "%d %d %lf", &row, &column, &data);
    changeEntry(A, row, column, data);
  }
  Matrix B = newMatrix(n);
  // fill in matrix B
  for (int i = 0; i < b; i++) {
    fscanf(input, "%d %d %lf", &row, &column, &data);
    changeEntry(B, row, column, data);
  }
  fclose(input);
  // output = stdout;
  fprintf(output, "A has %d non-zero entries:\n", a);
  printMatrix(output, A);
  fprintf(output, "\n");
  fprintf(output, "B has %d non-zero entries:\n", b);
  printMatrix(output, B);
  fprintf(output, "\n");

  fprintf(output, "(1.5)*A =\n");
  Matrix C = scalarMult(1.5, A);
  printMatrix(output, C);
  fprintf(output, "\n");
  freeMatrix(&C);

  fprintf(output, "A+B =\n");
  C = sum(A, B);
  printMatrix(output, C);
  fprintf(output, "\n");
  freeMatrix(&C);

  fprintf(output, "A+A =\n");
  C = sum(A, A);
  printMatrix(output, C);
  fprintf(output, "\n");
  freeMatrix(&C);

  fprintf(output, "B-A =\n");
  C = diff(B, A);
  printMatrix(output, C);
  fprintf(output, "\n");
  freeMatrix(&C);

  fprintf(output, "A-A =\n");
  C = diff(A, A);
  printMatrix(output, C);
  fprintf(output, "\n");
  freeMatrix(&C);

  fprintf(output, "Transpose(A) =\n");
  C = transpose(A);
  printMatrix(output, C);
  fprintf(output, "\n");
  freeMatrix(&C);

  fprintf(output, "A*B =\n");
  C = product(A, B);
  printMatrix(output, C);
  fprintf(output, "\n");
  freeMatrix(&C);

  fprintf(output, "B*B =\n");
  C = product(B, B);
  printMatrix(output, C);
  fprintf(output, "\n");
  freeMatrix(&C);

  freeMatrix(&A);
  freeMatrix(&B);
  fclose(output);
  return 0;
}
