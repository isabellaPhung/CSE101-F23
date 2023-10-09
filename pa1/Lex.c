// Isabella Phung
// Student ID: 1702285
// Assignment: pa1
// for CSE 101 Fall 2023

#include "List.h"
#include "string.h"
#include <stdio.h>
#include <stdlib.h>

int MAX_STRING_LENGTH =
    255; // maximum length of 1 line for string array allocation

int main(int argc, char **argv) {
  if (argc != 3) {
    fprintf(stderr, "Less than two command line arguments given! Please "
                    "provide input file and output file.");
    exit(EXIT_FAILURE);
  }
  FILE *input = fopen(argv[1], "r");
  FILE *output = fopen(argv[2], "w");
  if (input == NULL) {
    fprintf(stderr, "Could not open %s.\n", argv[1]);
    fclose(output);
    exit(EXIT_FAILURE);
  }

  // counts lines in input file
  int lineCount = 0;
  for (char ch = getc(input); ch != EOF; ch = getc(input)) {
    if (ch == '\n') {
      lineCount++;
    }
  }
  // printf("%d\n", lineCount); //lineCount test

  // preparing string array
  char **strArray = calloc(lineCount, sizeof(char *));
  for (int i = 0; i < lineCount; i++) {
    strArray[i] = (char *)malloc(MAX_STRING_LENGTH);
  }
  // string array prepared

  // puts string info from file into array
  rewind(input); // resets input pointer
  for (int i = 0; i < lineCount; i++) {
    fgets(strArray[i], MAX_STRING_LENGTH, input);
  }

  // testing string array
  /**
  for(int i = 0; i < lineCount; i++){
      printf("%s", strArray[i]);
  }
  **/

  fclose(input);

  List sorted = newList();
  append(sorted, 0);
  moveFront(sorted);
  // perform insertion sort
  for (int i = 1; i < lineCount; i++) {
    while (1) {
      if (index(sorted) == -1) {
        append(sorted, i);
        break;
      }
      int compare = strcmp(strArray[get(sorted)], strArray[i]);
      if (compare >= 0) { // if belongs left or equivalent, insert before
        insertBefore(sorted, i);
        break;
      }
      moveNext(sorted);
    }
    moveFront(sorted);
  }
  // printList(stdout, sorted);

  moveFront(sorted);
  for (int i = 0; i < lineCount; i++) {
    fprintf(output, "%s", strArray[get(sorted)]);
    moveNext(sorted);
  }
  fclose(output);

  // freeing allocated memory for string array
  for (int i = 0; i < lineCount; i++) {
    free(strArray[i]);
    strArray[i] = NULL;
  }
  free(strArray);
  strArray = NULL;

  freeList(&sorted); // free List ADT
  return 0;
}
