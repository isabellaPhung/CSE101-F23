/***
* Isabella Phung
* itphung
* 2023 Fall CSE 101 PA3
* FindComponents.c
* Client program for Graph ADT that makes graphs from files and finds connected components
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
  //printf("verticies: %d", getOrder(G));
  int origin = -1;
  int termina = -1;
  fscanf(input, "%d %d", &origin, &termina);
  while (origin != 0) {
    //printf("O-T: %d %d\n", origin, termina);
    addArc(G, origin, termina);
    fscanf(input, "%d %d", &origin, &termina);
  }
  printGraph(output, G);

  freeGraph(&G);
  fclose(input);
  fclose(output);
  return 0;
}
