/***
* Isabella Phung
* itphung
* 2023 Fall CSE 101 PA3
* Graph.h
* Header file for Graph ADT
***/

#pragma once

#ifndef GRAPH_H_INCLUDE_
#define GRAPH_H_INCLUDE_

#include "List.h"
#include <stdio.h>

#define INF -1
#define NIL 0
#define UNDEF -1

typedef struct GraphObj *Graph;

/*** Constructors-Destructors ***/

// returns Graph pointing to GraphObj
// has n verticies and no edges
Graph newGraph(int n);

// frees all heap memory associated with Graph *pG
// and sets *pG to NULL
void freeGraph(Graph *pG);

/*** Access functions ***/

// returns order of Graph G
int getOrder(Graph G);

// returns size of Graph G
int getSize(Graph G);

// returns parent of vertex u in G
// or NIL if DFS() not called yet
// Pre: 1<=u<=getOrder(G)
int getParent(Graph G, int u);

// returns discover time of vertex u in G
// or NIL if DFS() not called yet
// Pre: 1<=u<=getOrder(G)
int getDiscover(Graph G, int u);

// returns finish time of vertex u in G
// or NIL if DFS() not called yet
// Pre: 1<=u<=getOrder(G)
int getFinish(Graph G, int u);

// returns source vertex most recently used in BFS()
// or NIL if BFS() not called yet
int getSource(Graph G);

// returns parent of vertex u used in BFS() or DFS()
// or NIL if BFS() and DFS() have not been called yet
// Pre: 1<=u<=getOrder(g)
int getParent(Graph G, int u);

// returns distance from most recent BFS source to vertex u
// or INF if BFS() not called yet
// Pre: 1<=u<=getOrder(g)
int getDist(Graph G, int u);

// appends to List L verticies of shortest path in G to u
// or appends NIL to L if no path exists
// Pre: getSource(G) != NIL (BFS must have been called)
// Pre: 1<=u<=getOrder(g)
void getPath(List L, Graph G, int u);

/*** Manipulation procedures ***/

// deletes all edges of G
void makeNull(Graph G);

// inserts new edge connecting u and v
// Pre: 1<=u,v<=getOrder(G)
void addEdge(Graph G, int u, int v);

// inserts new directed edge from u to v
// Pre: 1<=u,v<=getOrder(G)
void addArc(Graph G, int u, int v);

// runs BFS algorithm on Graph G with source s
// sets color, distance, parent, and source fields
void BFS(Graph G, int s);

// runs DFS algorithm on Graph G with List S
// sets discover, color, parent and finish fields
void DFS(Graph G, List s);

/*** Other operations ***/
//transposes given graph
Graph transpose(Graph G);

//creates identical copy of given graph
Graph copyGraph(Graph G);

// prints adjacency list representation of G to file out
void printGraph(FILE *out, Graph G);

#endif
