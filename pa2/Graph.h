#ifndef LIST_H_INCLUDE_
#define LIST_H_INCLUDE_

#define INF -1
#define NIL 0

#include<List.h>

typedef struct GraphObj *Graph;

/*** Constructors-Destructors ***/ 

//returns Graph pointing to GraphObj
//has n verticies and no edges
Graph newGraph(int n); 

//frees all heap memory associated with Graph *pG
//and sets *pG to NULL
void freeGraph(Graph* pG); 
 
/*** Access functions ***/ 

//returns order of Graph G
int getOrder(Graph G); 

//returns size of Graph G
int getSize(Graph G); 

//returns source vertex most recently used in BFS()
//or NIL if BFS() not called yet
int getSource(Graph G); 

//returns parent of vertex u used in BFS()
//or NIL if BFS() not called yet
//Pre: 1<=u<=getOrder(g)
int getParent(Graph G, int u); 

//returns distance from most recent BFS source to vertex u
//or INF if BFS() not called yet
//Pre: 1<=u<=getOrder(g)
int getDist(Graph G, int u); 

//appends to List L verticies of shortest path in G to u
//or appends NIL to L if no path exists
//Pre: getSource(G) != NIL (BFS must have been called)
//Pre: 1<=u<=getOrder(g)
void getPath(List L, Graph G, int u); 
 
/*** Manipulation procedures ***/ 

//deletes all edges of G
void makeNull(Graph G); 

//inserts new edge connecting u and v
//Pre: 1<=u,v<=getOrder(G)
void addEdge(Graph G, int u, int v);

//inserts new directed edge from u to v
//Pre: 1<=u,v<=getOrder(G)
void addArc(Graph G, int u, int v);

//runs BFS algorithm on Graph G with source s
//sets color, distance, parent, and source fields
void BFS(Graph G, int s); 
 
/*** Other operations ***/ 
//prints adjacency list representation of G to file out
void printGraph(FILE* out, Graph G);

#endif
