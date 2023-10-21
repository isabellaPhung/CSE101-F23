// Isabella Phung
// Student ID: 1702285
// Assignment: pa3
// for CSE 101 Fall 2023

#include "Graph.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

  printf("Test 1:\n");
  int verticies = 6;
  Graph G = newGraph(verticies);

  addArc(G, 1, 2);
  addArc(G, 3, 1);
  addArc(G, 2, 4);
  addArc(G, 2, 5);
  addArc(G, 2, 6);
  addArc(G, 3, 4);
  addArc(G, 4, 5);
  addArc(G, 5, 6);
  printGraph(stdout, G);
  //addEdge(G, 11, 14);
  
  printf("Order: %d\n", getOrder(G));
  printf("Size: %d\n", getSize(G));
  printf("Parent of 1: %d\n", getParent(G, 1));
  
  List s = newList();

  for(int i = 1; i<getOrder(G)+1; i++){
    append(s, i);
  }
  printf("s before first DFS: ");
  printList(stdout, s);
  DFS(G, s); 
  printf("s after first DFS: ");
  printList(stdout, s);
  Graph GT = transpose(G);
  DFS(GT, s);
  printf("Transpose DFS performed:\n");
  printf("s and corresponding parents:\n");
  moveFront(s);
  for(int i = 1; i<getOrder(G)+1; i++){
    printf("%d %d\n", get(s), getParent(GT, get(s)));
    moveNext(s);
  }
  freeGraph(&G);
  freeGraph(&GT);
  
  printf("\nTest 2:\n");
  G = newGraph(4); 
  addArc(G, 1, 2);
  addArc(G, 3, 1);
  addArc(G, 2, 3);
  addArc(G, 3, 4);
  addArc(G, 4, 2);
  printGraph(stdout, G);
  //addEdge(G, 11, 14);
  
  clear(s);

  for(int i = 1; i<getOrder(G)+1; i++){
    append(s, i);
  }
  printf("s before first DFS: ");
  printList(stdout, s);
  DFS(G, s); 
  printf("s after first DFS: ");
  printList(stdout, s);
  GT = transpose(G);
  DFS(GT, s);
  printf("Transpose DFS performed:\n");
  printf("s and corresponding parents:\n");
  moveFront(s);
  for(int i = 1; i<getOrder(G)+1; i++){
    printf("%d %d\n", get(s), getParent(GT, get(s)));
    moveNext(s);
  }
  freeList(&s);
  freeGraph(&G);
  freeGraph(&GT);
  return 0;
}
