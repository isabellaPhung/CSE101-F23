/***
* Isabella Phung
* itphung
* 2023 Fall CSE 101 PA2
* FindPath.c
* Client program for Graph ADT that makes graphs from files
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
  int verticies = 0;
  fscanf(input, "%d", &verticies);
  Graph G = newGraph(verticies);
  //printf("verticies: %d", getOrder(G));
  int origin = -1;
  int termina = -1;
  fscanf(input, "%d %d", &origin, &termina);
  while (origin != 0) {
    //printf("O-T: %d %d\n", origin, termina);
    addEdge(G, origin, termina);
    fscanf(input, "%d %d", &origin, &termina);
  }
  printGraph(output, G);

  origin = -1;
  termina = -1;
  // find shortest path
  List path = newList();
  fscanf(input, "%d %d", &origin, &termina);
  while (termina != 0) {
    fprintf(output, "\n");
    BFS(G, origin);
    getPath(path, G, termina);

    // print info out
    if(getDist(G, termina)==INF){
      fprintf(output, "The distance from %d to %d is infinity\n", origin, termina);
   
    } else{
    fprintf(output, "The distance from %d to %d is %d\n", origin, termina, getDist(G, termina));
    }

    if (front(path) == NIL) {
      fprintf(output, "No %d-%d path exists\n", origin, termina);
    } else {
      fprintf(output, "A shortest %d-%d path is: ", origin, termina);
      printList(output, path);
    }
    clear(path);
    fscanf(input, "%d %d", &origin, &termina);
  }
  freeList(&path);
  freeGraph(&G);
  fclose(input);
  fclose(output);
  return 0;
}
