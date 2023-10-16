#include "Graph.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int verticies = 6;
  Graph G = newGraph(verticies);

  
  addEdge(G, 1, 2);
  addEdge(G, 3, 1);
  addEdge(G, 2, 4);
  addEdge(G, 2, 5);
  addEdge(G, 2, 6);
  addEdge(G, 3, 4);
  addEdge(G, 4, 5);
  addEdge(G, 5, 6);
  printGraph(stdout, G);
  //addEdge(G, 11, 14);
  
  printf("Order: %d\n", getOrder(G));
  printf("Size: %d\n", getSize(G));
  printf("Source: %d\n", getSource(G));
  printf("Parent of 1: %d\n", getParent(G, 1));
  printf("Dist: %d\n", getDist(G, 2));
  List L = newList();
  getPath(L, G, 2);
  printf("Path from 1 to 2 before BFS: ");
  printList(stdout, L);
  clear(L);

  BFS(G, 3);
  printf("\nBFS Run with source %d:\n", getSource(G));
  
  int goal = 6;
  getPath(L, G, goal);
  printf("Path from 3 to %d after BFS: ", goal);
  printList(stdout, L);
  printf("Dist: %d\n", getDist(G, goal));
  printf("Parent of %d: %d\n", goal, getParent(G, goal));
  printf("\n");
  clear(L);

  goal = 5;
  getPath(L, G, goal);
  printf("Path from 3 to %d after BFS: ", goal);
  printList(stdout, L);
  printf("Dist: %d\n", getDist(G, goal));
  printf("Parent of %d: %d\n", goal, getParent(G, goal));
  freeList(&L);

  freeGraph(&G);
  return 0;
}
