/***
* Isabella Phung
* itphung
* 2023 Fall CSE 101 PA4
* Matrix.c
* Implementation file for Matrix ADT
***/

#include"Matrix.h"
#include<stdbool.h>
#include<stdlib.h>
#include<assert.h>

// private Entry type
typedef struct EntryObj *Entry;

// private EntryObj type
typedef struct EntryObj {
    int col;
    double data;
} EntryObj;

// private MatrixObj type
typedef struct MatrixObj {
  int size;
  int nnz;
  List *row;
} MatrixObj;

Entry newEntry(int col, double data){
    Entry E = malloc(sizeof(EntryObj));
    assert(E != NULL);
    E->col = col;
    E->data = data;
    return E;
}

void freeEntry(Entry* pE){
    if (pE != NULL && *pE != NULL) { // checks if Entry is Null
        free(*pE);
        *pE = NULL; // dereferences pM and pointer to null
    }
}

// newMatrix() 
// Returns a reference to a new nXn Matrix object in the zero state. 
Matrix newMatrix(int n){
    Matrix M = malloc(sizeof(MatrixObj));
    assert(M != NULL);
    M->size = n;
    M->row = calloc(n+1, sizeof(List *));
    for (int i = 1; i < n+1; i++) {
        M->row[i] = newList();
    }
    M->nnz = 0;
    return M;
}
  
// makeZero() 
// Re-sets M to the zero Matrix state. 
void makeZero(Matrix M){
    if (M == NULL) {
        printf("Matrix Error: calling makeZero() on NULL Matrix.\n");
        exit(EXIT_FAILURE);
    }
    Entry entry;
    for(int i = 1; i < size(M)+1; i++){
        moveFront(M->row[i]); 
        while(index(M->row[i])!= -1){
            entry = get(M->row[i]);
            freeEntry(&entry);
            moveNext(M->row[i]);
        }
        clear(M->row[i]);
    }
    M->nnz = 0;
}

// freeMatrix() 
// Frees heap memory associated with *pM, sets *pM to NULL. 
void freeMatrix(Matrix* pM){
    if (pM != NULL && *pM != NULL) { // checks if Matrix is empty
        makeZero(*pM); 
        for (int i = 1; i < size(*pM)+1; i++) {
          freeList(&((*pM)->row[i]));
        }
        free((*pM)->row);
        (*pM)->row = NULL;
        free(*pM);
        *pM = NULL; // dereferences pM and pointer to null
    }
}
 
// Access functions  
 
// size() 
// Return the size of square Matrix M. 
int size(Matrix M){
    if (M == NULL) {
        printf("Matrix Error: calling size() on NULL Matrix.\n");
        exit(EXIT_FAILURE);
    }
    return M->size;
}
 
// NNZ() 
// Return the number of non-zero elements in M. 
int NNZ(Matrix M){
    if (M == NULL) {
        printf("Matrix Error: calling NNZ() on NULL Matrix.\n");
        exit(EXIT_FAILURE);
    }
    return M->nnz;
}


// equals() 
// Return true (1) if matrices A and B are equal, false (0) otherwise. 
int equals(Matrix A, Matrix B){
    if(A->size != B->size || A->nnz != B->nnz){
        return 0;
    }

    if (A == NULL || B == NULL) {
        printf("Matrix Error: calling equals() on NULL Matrix.\n");
        exit(EXIT_FAILURE);
    }
    Entry entryA;
    Entry entryB;
    for(int i = 1; i < size(A)+1; i++){
        //printf("hi\n");
        moveFront(A->row[i]);
        moveFront(B->row[i]);
        while(index(A->row[i]) != -1 && index(B->row[i]) != -1 ){
            entryA = get(A->row[i]);
            entryB = get(B->row[i]);
            if(entryA->col != entryB->col || entryA->data != entryB->data){
                return 0;
            }
            moveNext(A->row[i]);
            moveNext(B->row[i]);
        }
    }
    return 1;
}
 
 
// Manipulation procedures  
 
void printList(FILE *out, List L) {
  if (L == NULL) {
    printf("List Error: calling printList() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  
  moveFront(L);
  Entry entry;
  while(index(L)!=-1){
    entry = get(L);
    fprintf(out, "(%d, %.1f) ", entry->col, entry->data);
    moveNext(L);
  }
  
  fprintf(out, "\n");
}

// changeEntry() 
// Changes the ith row, jth column of M to the value x. 
// Pre: 1<=i<=size(M), 1<=j<=size(M) 
void changeEntry(Matrix M, int i, int j, double x){
    if (M == NULL) {
        printf("Matrix Error: calling changeEntry() on NULL Matrix.\n");
        exit(EXIT_FAILURE);
    }
    if (i < 1 || i > size(M)) {
        printf("Matrix Error when calling changeEntry(): row value needs to be 1<=i<=size(M).\n");
        exit(EXIT_FAILURE);
    }
    if (j < 1 || j > size(M)) {
        printf("Matrix Error when calling changeEntry(): column value needs to be 1<=j<=size(M).\n");
        exit(EXIT_FAILURE);
    }
    //first check if entry already exists
    List rowi = M->row[i];
    moveFront(rowi);
    Entry entry;
    Entry n;
    
    while(index(rowi) != -1){
        entry = get(rowi);
        if(entry -> col == j){//if entry exists
            if(x == 0){//if we're changing an existing val to 0, delete entry
                //printf("deleting existing val\n"); 
                M->nnz--;
                freeEntry(&entry);
                delete(rowi);
                return;
            }else{ //if we're changing an existing val
                entry->data = x; 
                //printf("changing existing val\n"); 
                return;
            }
        }
        if(entry -> col > j){
            if(x != 0){ //if no existing val
                M->nnz++;
                //printf("insertBefore reached\n");
                n = newEntry(j, x);
                insertBefore(rowi, n);
            }
            return;
        }
        moveNext(rowi);
    }
    //if we reached end of List, and data isn't 0, append to end
    if(x != 0){
        n = newEntry(j, x);
        append(rowi, n);
        M->nnz++;
    }
}

// Helper functions
//calculates dot product
double DotProd(List A, List B){
    double sum = 0;
    if(length(A)==0||length(B)==0){//if either lists empty
        return sum;
    }
    moveFront(A);
    moveFront(B);
    Entry entryA;
    Entry entryB;

    //neither A or B are empty
    while(index(A)!=-1 && index(B)!= -1){
       entryA = get(A);
       entryB = get(B);

       if(entryA -> col == entryB -> col){
            sum+=entryA->data*entryB->data;
            moveNext(A);
            moveNext(B);
            continue;       
       } else if(entryA -> col < entryB -> col){
            moveNext(A);
       }else{
            moveNext(B);
       }
    }
    return sum;
}

//adds and subtracts lists
//assumes lists are of same size
//int isAdd is either 1 or -1
List sumDiff(List A, List B, int isAdd){
    List sum = newList();
    Entry entry;
    Entry entryA;
    Entry entryB;

    moveFront(A);
    moveFront(B);

    //if either lists are empty,
    //copy contents of other list into sum
    if(length(A)==0){
        while(index(B)!=-1){
            entryB = get(B);
            entry = newEntry(entryB->col, isAdd*(entryB->data));
            append(sum, entry);
            moveNext(B);
        }
        return sum;
    }

    if(length(B)==0){
        while(index(A)!=-1){
            entryA = get(A);
            entry = newEntry(entryA->col, entryA->data);
            append(sum, entry);
            moveNext(A);
        }
        return sum;
    }
    
    //neither lists are empty
    double total = 0;
    while(index(A)!=-1 && index(B)!= -1){
       entryA = get(A);
       entryB = get(B);
       //printf("List A: ");
       //printList(stdout, A);
       //printf("List B: ");
       //printList(stdout, B);
       if(entryA -> col < entryB -> col){
            entry = newEntry(entryA->col, entryA->data);
            append(sum, entry);
            moveNext(A);
       }else if (entryA -> col > entryB -> col){
            entry = newEntry(entryB->col, isAdd*(entryB->data));
            append(sum, entry);
            moveNext(B);
       }else {
            total = entryA->data + isAdd*(entryB->data);
            if(total != 0){ //only append to sum if total isn't 0
                entry = newEntry(entryA->col, total);
                append(sum, entry);
            }
            moveNext(A);
            moveNext(B);
       }
    }

    //if we finished with extra remaining entries
    //at the end of any lists
    while(index(A)!=-1){
        entryA = get(A);
        entry = newEntry(entryA->col, entryA->data);
        append(sum, entry);
        moveNext(A);
    }
     
    while(index(B)!=-1){
        //printList(stdout, B);

        entryB = get(B);
        //printf("B index: %d entry B col: %d data: %lf\n", index(B), entryB->col, entryB->data);
        entry = newEntry(entryB->col, isAdd*(entryB->data));
        append(sum, entry);
        moveNext(B);
    }
    //printf("\n");

    return sum;
}
 
// Matrix Arithmetic operations  
 
// copy() 
// Returns a reference to a new Matrix object having the same entries as A. 
Matrix copy(Matrix A){
    Matrix B = newMatrix(size(A));
    Entry n;
    Entry entry;
    List rowi;
    for(int i = 1; i < size(B)+1; i++){
        rowi = A->row[i]; 
        moveFront(rowi);
        while(index(rowi)!=-1){
            entry = get(rowi);
            n = newEntry(entry->col, entry->data);
            append(B->row[i], n);
            moveNext(rowi);
        }
    }
    B->nnz = A->nnz;
    return B;
}
 
// transpose() 
// Returns a reference to a new Matrix object representing the transpose 
// of A. 
Matrix transpose(Matrix A){
    Matrix B = newMatrix(size(A));
    Entry entry;
    Entry n;
    List rowi;
    for(int i = 1; i < size(B)+1; i++){
        rowi = A->row[i]; 
        moveFront(rowi);
        while(index(rowi)!=-1){
            if(index(rowi) != -1){
                entry = get(rowi);
                n = newEntry(i, entry->data);
                append(B->row[entry->col], n);
                moveNext(rowi);
            }
        }
    }
    B->nnz = A->nnz;
    return B;

}
 
// scalarMult() 
// Returns a reference to a new Matrix object representing xA. 
Matrix scalarMult(double x, Matrix A){
    Matrix B = newMatrix(size(A));
    Entry entry;
    Entry n;
    List rowi;
    for(int i = 1; i < size(B)+1; i++){
        rowi = A->row[i]; 
        moveFront(rowi);
        while(index(rowi)!=-1){
            entry = get(rowi);
            n = newEntry(entry->col, x*(entry->data));
            append(B->row[i], n);
            moveNext(rowi);
        }
    }
    B->nnz = A->nnz;
    return B;
}
 
// sum() 
// Returns a reference to a new Matrix object representing A+B. 
// pre: size(A)==size(B) 
Matrix sum(Matrix A, Matrix B){
    if (size(A)!= size(B)) {
        printf("Matrix Error: calling sum() on matricies of different sizes.\n");
        exit(EXIT_FAILURE);
    }
    Matrix RH = B;
    int isDifferent = 1;
    if(equals(A, B)==1){
        RH = copy(B);
        isDifferent = 0;
    }
    Matrix C = newMatrix(size(A));
    for(int i = 1; i < size(RH)+1; i++){
        //printf("A row:");
        //printList(stdout, A->row[i]);
        //printf("B row:");
        //printList(stdout, RH->row[i]);

        freeList(&(C->row[i]));
        C->row[i]=sumDiff(A->row[i], RH->row[i], 1);
        C->nnz+=length(C->row[i]);
    }
    if(!isDifferent){
        freeMatrix(&RH);
    }
    return C;
}
 
// diff() 
// Returns a reference to a new Matrix object representing A-B. 
// pre: size(A)==size(B) 
Matrix diff(Matrix A, Matrix B){
    if (size(A) != size(B)) {
        printf("Matrix Error: calling diff() on matricies of different sizes.\n");
        exit(EXIT_FAILURE);
    }

    Matrix RH = B;
    int isDifferent = 1;
    if(equals(A, B)==1){
        RH = copy(B);
        isDifferent = 0;
    }

    Matrix C = newMatrix(size(A));
    for(int i = 1; i < size(RH)+1; i++){
        freeList(&(C->row[i]));
        C->row[i]=sumDiff(A->row[i], RH->row[i], -1); 
        C->nnz+=length(C->row[i]);
    }
    if(!isDifferent){
        freeMatrix(&RH);
    }
    return C;
}
 
// product() 
// Returns a reference to a new Matrix object representing AB 
// pre: size(A)==size(B) 
Matrix product(Matrix A, Matrix B){
    if (size(A) != size(B)) {
        printf("Matrix Error: calling diff() on matricies of different sizes.\n");
        exit(EXIT_FAILURE);
    }
    double data;
    Entry entry;

    Matrix C = newMatrix(size(A));
    Matrix BT = transpose(B);
    for(int i = 1; i<size(BT)+1;i++){
        if(length(BT->row[i])!=0){
            for(int j = 1; j<size(A)+1; j++){
               if(length(A->row[j])!=0){
                    data = DotProd(A->row[j], BT->row[i]);
                    if(data != 0){
                        entry = newEntry(i, data);
                        append(C->row[j], entry);
                        C->nnz++;
                    }
               }
           }
        }
        
    }
    freeMatrix(&BT);
    return C;
}
 
// printMatrix() 
// Prints a string representation of Matrix M to filestream out. Zero rows  
// are not printed.  Each non-zero row is represented as one line consisting  
// of the row number, followed by a colon, a space, then a space separated  
// list of pairs "(col, val)" giving the column numbers and non-zero values  
// in that row. The double val will be rounded to 1 decimal point. 
void printMatrix(FILE* out, Matrix M){
    for(int i = 1; i<size(M)+1; i++){
        if(length(M->row[i]) != 0){
            fprintf(out, "%d: ", i);
            printList(out, M->row[i]);
        }
    }
}
