/***
 * Isabella Phung
 * itphung
 * 2023 Fall CSE 101 PA3
 * FindComponents.c
 * Client program for Graph ADT that makes graphs from files and finds connected
 *components
 ***/

#include "Graph.h"

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

  // build adj matrix
  fprintf(output, "Adjacency list representation of G:\n");
  int verticies = 0;
  fscanf(input, "%d", &verticies);
  Graph G = newGraph(verticies);
  // printf("verticies: %d", getOrder(G));
  int origin = -1;
  int termina = -1;
  fscanf(input, "%d %d", &origin, &termina);
  while (origin != 0) {
    // printf("O-T: %d %d\n", origin, termina);
    addArc(G, origin, termina);
    fscanf(input, "%d %d", &origin, &termina);
  }
  printGraph(output, G);

  // create s list
  List s = newList();
  for (int i = 1; i < getOrder(G) + 1; i++) {
    append(s, i);
  }
  DFS(G, s);

  Graph GT = transpose(G);

  DFS(GT, s);

  // need to count the number of components
  int componentCount = 0;
  moveBack(s);
  while (index(s) != -1) {
    if (getParent(GT, get(s)) == NIL) {
      componentCount++;
    }
    movePrev(s);
  }

  fprintf(output, "\n");
  fprintf(output, "G contains %d strongly connected components:\n",
          componentCount);

  moveBack(s);
  List temp = newList();
  for (int i = 1; i <= componentCount; i++) {
    fprintf(output, "Component %d: ", i);
    prepend(temp, get(s));
    while (getParent(GT, get(s)) != NIL && index(s) != -1) {
      movePrev(s);
      prepend(temp, get(s));
    }
    printList(output, temp);
    clear(temp);
    movePrev(s);
  }

  freeList(&s);
  freeList(&temp);
  freeGraph(&G);
  freeGraph(&GT);
  fclose(input);
  fclose(output);
  return 0;
}
