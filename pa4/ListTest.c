#include "List.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  List A = newList();
  List B = newList();

  int *x = calloc(20, sizeof(int *));
  for (int i = 1; i <= 20; i++) {
    x[i - 1] = i;
  }

  for (int i = 0; i < 20; i++) {
    append(A, &x[i]);
    prepend(B, &x[i]);
  }

  moveFront(A);
  printf("A: ");
  while (index(A) != -1) {
    printf("%d, ", *(int *)get(A));
    moveNext(A);
  }
  printf("\n");

  moveFront(B);
  printf("B: ");
  while (index(B) != -1) {
    printf("%d, ", *(int *)get(B));
    moveNext(B);
  }
  printf("\n");

  moveFront(A);
  moveFront(B);
  while (index(A) != -1) {
    if (get(A) != get(B)) {
      printf("A not equal to B\n");
      break;
    }
    moveNext(A);
    moveNext(B);
  }

  List C = newList();
  moveFront(A);
  while (index(A) != -1) {
    append(C, get(A));
    moveNext(A);
  }

  moveFront(C);
  printf("A Copy: ");
  while (index(C) != -1) {
    printf("%d, ", *(int *)get(C));
    moveNext(C);
  }
  printf("\n");

  moveFront(A);
  moveFront(C);
  while (index(A) != -1) {
    if (get(A) != get(C)) {
      printf("A not equal to C\n");
      break;
    }
    moveNext(A);
    moveNext(C);
  }
  printf("A is equal to its copy\n");

  // check length of A, before and after clear()
  printf("length of A before clear: %d\n", length(A));
  clear(A);
  printf("length of A after clear: %d\n", length(A));

  freeList(&A);
  freeList(&B);
  freeList(&C);

  return (0);
}
