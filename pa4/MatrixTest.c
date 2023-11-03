//-----------------------------------------------------------------------------
// ListClient.c
// Test client for List ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include"Matrix.h"

int main(int argc, char* argv[]){
    int k = 10;
    Matrix M = newMatrix(3);
    /**
    changeEntry(M, 1, 1, 1);
    printMatrix(stdout, M);

    changeEntry(M, 1, 2, 2);
    printMatrix(stdout, M);
    **/ 

    printf("Size: %d\n", size(M));
    for(int i = 3; i>0; i--){
        for(int j = 3; j>0; j--){
            k--;
            //printf("k: %d\n", k);
            changeEntry(M, i, j, k);
        }
    }

    printMatrix(stdout, M);
    printf("NNZ: %d\n", NNZ(M));
    printf("\n");
    
    changeEntry(M, 1, 3, 0);
    printMatrix(stdout, M);
    printf("NNZ: %d\n", NNZ(M));
    printf("\n");
    
    changeEntry(M, 1, 3, 0);
    printMatrix(stdout, M);
    printf("NNZ: %d\n", NNZ(M));
    printf("\n");

    printf("Transpose Test:\n");
    Matrix MT = transpose(M);
    printMatrix(stdout, MT);
    printf("NNZ: %d\n", NNZ(MT));
    printf("\n");

    changeEntry(M, 1, 3, 27);
    printMatrix(stdout, M);
    printf("NNZ: %d\n", NNZ(M));
    printf("\n");

    changeEntry(M, 1, 3, 30);
    printMatrix(stdout, M);
    printf("NNZ: %d\n", NNZ(M));
    printf("\n");
  
    printf("Transpose Test:\n");
    Matrix AT = transpose(M);
    printMatrix(stdout, AT);
    printf("NNZ: %d\n", NNZ(AT));
    printf("\n");
    
    printf("Scalar Mult Test:\n");
    Matrix C = scalarMult(2, M);
    printMatrix(stdout, C);
    printf("\n");

    printf("Sum Test:\n");
    Matrix E = copy(M);
    Matrix D = sum(M, E);
    printMatrix(stdout, D);
    printf("\n");

    printf("Diff Test:\n");
    Matrix F = diff(D, E);
    printMatrix(stdout, F);
    printf("\n");
    
    changeEntry(M, 1, 3, 0);
    printMatrix(stdout, M);
    printf("NNZ: %d\n", NNZ(M));
    printf("\n");

    printf("Copy Test:\n");
    Matrix A = copy(M);
    printMatrix(stdout, A);
    printf("NNZ: %d\n", NNZ(A));
    printf("\n");

    printf("Equals Test:\n");
    if(equals(M, A)==1){
        printf("M and A are equal\n");
    }else{
        printf("M and A are not equal\n");
    }
    printf("\n");

    printf("Equals Test:\n");
    if(equals(M, MT)==1){
        printf("M and MT are equal\n");
    }else{
        printf("M and MT are not equal\n");
    }
    printf("\n");

    printf("Product Test:\n");
    Matrix G = product(M, A);
    printMatrix(stdout, G);
    printf("\n");

    printf("Sum Test:\n");
    Matrix H = copy(AT);
    Matrix Z = transpose(H);
    Matrix I = copy(Z);
    changeEntry(I, 2, 1, -4);
    changeEntry(I, 2, 2, -5);
    changeEntry(I, 2, 3, -6);
    printf("Matrix H:\n");
    printMatrix(stdout, Z);
    printf("Matrix I:\n");
    printMatrix(stdout, I);
    Matrix J = sum(Z, I);
    printf("Sum Matrix J:\n");
    printMatrix(stdout, J);
    printf("NNZ: %d\n", NNZ(J));
    printf("\n");
    printf("Diff Test:\n");
    Matrix K = diff(Z, I);
    printMatrix(stdout, K);
    printf("NNZ: %d\n", NNZ(K));
    printf("\n");
    
    freeMatrix(&Z);
    freeMatrix(&K);
    freeMatrix(&J);
    freeMatrix(&I);
    freeMatrix(&H);
    freeMatrix(&G);
    freeMatrix(&F);
    freeMatrix(&E);
    freeMatrix(&D);
    freeMatrix(&C);
    freeMatrix(&AT);
    freeMatrix(&A);
    freeMatrix(&MT);
    freeMatrix(&M);
    return 0;
}
