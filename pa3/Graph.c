/***
* Isabella Phung
* itphung
* 2023 Fall CSE 101 PA3
* Graph.c
* Implementation of Graph ADT
***/

#include "Graph.h"
#include "List.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// private GraphObj type, denoted with Graph
typedef struct GraphObj {
  int order;
  int size;
  List *adj;
  char *colors;
  int *parents;
  int *d;
  int s;
  int *discover;
  int *finish;
} GraphObj;

/*** Constructors-Destructors ***/

// returns Graph pointing to GraphObj
// has n verticies and no edges
Graph newGraph(int n) {
  Graph G;
  G = malloc(sizeof(GraphObj));
  assert(G != NULL); // checks allocation is not null
  G->order = n;
  G->size = NIL;

  G->adj = calloc(G->order + 1, sizeof(List *));
  for (int i = 1; i < ((G->order) + 1); i++) {
    G->adj[i] = newList();
  } // adj list of G

  G->colors = calloc(G->order + 1, sizeof(char)); // array of chars w, g, b
  // initializes all verticies as white
  for (int i = 1; i < ((G->order) + 1); i++) {
    G->colors[i] = 'w';
  }

  G->parents =
      calloc(G->order + 1,
             sizeof(int)); // ith element is the parent of the int element
  // initializes all parents as NIL
  for (int i = 1; i < ((G->order) + 1); i++) {
    G->parents[i] = NIL;
  }

  G->d = calloc(G->order + 1, sizeof(int)); // distance to recent source
  // init distances
  for (int i = 1; i < ((G->order) + 1); i++) {
    G->d[i] = INF;
  }

  G->s = NIL; // source vertex
  
  G->discover =
      calloc(G->order + 1,
             sizeof(int)); // stores discover time for DFS
  // initializes all discover time as undef
  for (int i = 1; i < ((G->order) + 1); i++) {
    G->discover[i] = UNDEF;
  }
    
  G->finish =
      calloc(G->order + 1,
             sizeof(int)); // stores finish time for DFS
  // initializes all finish time as undef
  for (int i = 1; i < ((G->order) + 1); i++) {
    G->finish[i] = UNDEF;
  }
  return G;
}

// frees all heap memory associated with Graph *pG
// and sets *pG to NULL
void freeGraph(Graph *pG) {
  if (pG != NULL && *pG != NULL) { // checks if Graph is empty
    for (int i = 1; i < (*pG)->order + 1; i++) {
      freeList(&((*pG)->adj[i]));
    }
    free((*pG)->adj);
    (*pG)->adj = NULL;
    free((*pG)->colors);
    (*pG)->colors = NULL;
    free((*pG)->parents);
    (*pG)->parents = NULL;
    free((*pG)->d);
    (*pG)->d = NULL;
    free(*pG);
    free((*pG)->discover);
    (*pG)->discover = NULL;
    free((*pG)->finish);
    (*pG)->finish = NULL;
    *pG = NULL; // dereferences pG and pointer to null
  }
}

/*** Access functions ***/

// returns order of Graph G
int getOrder(Graph G) {
  if (G == NULL) {
    printf("Graph Error: calling getOrder() on NULL Graph.\n");
    exit(EXIT_FAILURE);
  }
  return G->order;
}

// returns size of Graph G
int getSize(Graph G) {
  if (G == NULL) {
    printf("Graph Error: calling getSize() on NULL Graph.\n");
    exit(EXIT_FAILURE);
  }
  return G->size;
}

// returns discover time of vertex u in G
// or NIL if DFS() not called yet
// Pre: 1<=u<=getOrder(G)
int getDiscover(Graph G, int u){
  if (G == NULL) {
    printf("Graph Error: calling getDiscover() on NULL Graph.\n");
    exit(EXIT_FAILURE);
  }
  if (u < 1 || u > getOrder(G)) {
    printf("Graph Error: calling getDiscover() when u does not meet "
           "preconditons. Given u must be 1<=u<=getOrder(G).\n");
    exit(EXIT_FAILURE);
  }
  return G->discover[u];
}

// returns finish time of vertex u in G
// or NIL if DFS() not called yet
// Pre: 1<=u<=getOrder(G)
int getFinish(Graph G, int u){
  if (G == NULL) {
    printf("Graph Error: calling getFinish() on NULL Graph.\n");
    exit(EXIT_FAILURE);
  }
  if (u < 1 || u > getOrder(G)) {
    printf("Graph Error: calling getFinish() when u does not meet "
           "preconditons. Given u must be 1<=u<=getOrder(G).\n");
    exit(EXIT_FAILURE);
  }
  return G->finish[u];
}

// returns source vertex most recently used in BFS()
// or NIL if BFS() not called yet
int getSource(Graph G) {
  if (G == NULL) {
    printf("Graph Error: calling getSource() on NULL Graph.\n");
    exit(EXIT_FAILURE);
  }
  return G->s;
}

// returns parent of vertex u used in BFS() or DFS()
// or NIL if BFS() or DFS() have not been called yet
// Pre: 1<=u<=getOrder(g)
int getParent(Graph G, int u) {
  if (G == NULL) {
    printf("Graph Error: calling getParent() on NULL Graph.\n");
    exit(EXIT_FAILURE);
  }
  if (u < 1 || u > getOrder(G)) {
    printf("Graph Error: calling getParent() when u does not meet "
           "preconditons. Given u must be 1<=u<=getOrder(G).\n");
    exit(EXIT_FAILURE);
  }
  return G->parents[u];
}

// returns distance from most recent BFS source to vertex u
// or INF if BFS() not called yet
// Pre: 1<=u<=getOrder(g)
int getDist(Graph G, int u) {
  if (G == NULL) {
    printf("Graph Error: calling getDist() on NULL Graph.\n");
    exit(EXIT_FAILURE);
  }
  if (u < 1 || u > getOrder(G)) {
    printf("Graph Error: calling getDist() when u does not meet preconditons. "
           "Given u must be 1<=u<=getOrder(G).\n");
    exit(EXIT_FAILURE);
  }
  return G->d[u];
}

// appends to List L verticies of shortest path in G to u
// or appends NIL to L if no path exists
// Pre: getSource(G) != NIL (BFS must have been called)
// Pre: 1<=u<=getOrder(g)
void getPath(List L, Graph G, int u) {
  if (u < 1 || u > getOrder(G)) {
    printf("Graph Error: calling getPath() when u does not meet preconditons. "
           "Given u must be 1<=u<=getOrder(G).\n");
    exit(EXIT_FAILURE);
  }

  if (G->s == u) {
    append(L, G->s);
  } else if (G->parents[u] == NIL) {
    append(L, NIL);
  } else {
    getPath(L, G, G->parents[u]);
    append(L, u);
  }
}

/*** Manipulation procedures ***/

// deletes all edges of G
void makeNull(Graph G) {
  for (int i = 1; i < ((G->order) + 1); i++) {
    G->adj[i] = NULL;
  }
}

// inserts new edge connecting u and v
// maintains vertex order
// Pre: 1<=u,v<=getOrder(G)
void addEdge(Graph G, int u, int v) {
  if (u < 1 || u > getOrder(G)) {
    printf("Graph Error: calling addEdge() when u does not meet preconditons. "
           "Given u must be 1<=u<=getOrder(G).\n");
    exit(EXIT_FAILURE);
  }
  if (v < 1 || v > getOrder(G)) {
    printf("Graph Error: calling addEdge() when v does not meet preconditons. "
           "Given v must be 1<=v<=getOrder(G).\n");
    exit(EXIT_FAILURE);
  }

  // inserting v into u's adj list
  // checking for appropriate place
  if (length(G->adj[u]) == 0) { // if u has no adj
    append(G->adj[u], v);
  } else {
    moveFront(G->adj[u]);
    while(1){
      if (index(G->adj[u]) == -1) { // if at end of u's adj, append
        append(G->adj[u], v);
        break;
      } else if (v <= get(G->adj[u])) { // if before cursor, insert before
        insertBefore(G->adj[u], v);
        break;
      }
      moveNext(G->adj[u]);
    }
  }

  // inserting u into v's adj list
  // checking for appropriate place
  if (length(G->adj[v]) == 0) { // if v has no adj
    append(G->adj[v], u);
  } else {
    moveFront(G->adj[v]);
    while(1) {
      if (index(G->adj[v]) == -1) { // if at end of v's adj, append
        append(G->adj[v], u);
        break;
      } else if (u <= get(G->adj[v])) { // if before cursor, insert before
        insertBefore(G->adj[v], u);
        break;
      }
      moveNext(G->adj[v]);
    };
  }

  G -> size++;
  // u added to adjacency list of v, v added to adjacency of u
}

// Pre: 1<=u,v<=getOrder(G)
void addArc(Graph G, int u, int v) {
  if (u < 1 || u > getOrder(G)) {
    printf("Graph Error: calling addEdge() when u does not meet preconditons. "
           "Given u must be 1<=u<=getOrder(G).\n");
    exit(EXIT_FAILURE);
  }
  if (v < 1 || v > getOrder(G)) {
    printf("Graph Error: calling addEdge() when v does not meet preconditons. "
           "Given v must be 1<=v<=getOrder(G).\n");
    exit(EXIT_FAILURE);
  }

  // inserting v into u's adj list
  // checking for appropriate place
  if (length(G->adj[u]) == 0) { // if u has no adj
    append(G->adj[u], v);
  } else {
    moveFront(G->adj[u]);
    while (1){
      if (index(G->adj[u]) == -1) { // if at end of u's adj, append
        append(G->adj[u], v);
        break;
      } else if (v <= get(G->adj[u])) { // if before cursor, insert before
        insertBefore(G->adj[u], v);
        break;
      }
      moveNext(G->adj[u]);
    }
  }
  G -> size++;
}

// runs BFS algorithm on Graph G with source s
// sets color, distance, parent, and source fields
void DFS(Graph G, List s){
  for (int i = 1; i < ((G->order) + 1); i++) {
    G->colors[i] = 'w';
    G->parents[i] = NIL;
  }
  int time = 0;
  for (int i = 1; i < ((G->order) + 1); i++) {
    if(color[i] == 'w'){
        time = Visit(G, i, time);
    }
  }
}

int Visit(Graph G, int x, int time){
    discover[x] = ++time;
    color[x] = 'g';
    front(G->adj[x]);
    int y = 0;
    while(index(G->adj[x]) != -1){
        y = get(G->adj[x]);
        if(color[y]=='w'){
            parent[y] = x;
            Visit(G, y, time);
        }
        moveNext(G->adj[vertex]);
    }
    color[x] = 'b';
    finish[x] = ++time
    return time;
}

// runs BFS algorithm on Graph G with source s
// sets color, distance, parent, and source fields
void BFS(Graph G, int s) {
  G -> s = s;
  for (int i = 1; i < ((G->order) + 1); i++) {
    G->colors[i] = 'w';
    G->d[i] = INF;
    G->parents[i] = NIL;
  }
  G->colors[G->s] = 'g';
  G->d[G->s] = 0;
  G->parents[s] = NIL;
  List Q = newList();
  append(Q, s);
  int x;
  while (length(Q) != 0) {
    moveFront(Q);
    x = get(Q);
    deleteFront(Q);
    
    //maybe do a check here to see if adj list is empty
    int y;
    moveFront(G->adj[x]);
    while(index(G->adj[x])!=-1){
      y = get(G->adj[x]);
      if (G->colors[y] == 'w') {
        G->colors[y] = 'g';
        G->d[y] = G->d[x] + 1;
        G->parents[y] = x;
        append(Q, y);
      }
      moveNext(G->adj[x]);
    }
    G->colors[x] = 'b';
  } 
  freeList(&Q);
}

/*** Other operations ***/
//transposes given graph
Graph transpose(Graph G){
  Graph D = newGraph(G->order);
  for (int i = 1; i < ((G->order) + 1); i++) {
    front(G->adj[i]);
    while(index(G->adj[i]) != -1){
        addArc(get(G->adj[i]), i);
        moveNext(G->adj[i]);
    }
  }
  return D;
}

//creates identical copy of given graph
Graph copyGraph(Graph G){
  Graph D = newGraph(G->order);
  for (int i = 1; i < ((G->order) + 1); i++) {
    front(G->adj[i]);
    while(index(G->adj[i]) != -1){
        addArc(i, get(G->adj[i]));
        moveNext(G->adj[i]);
    }
  }
  return D;
}

// prints adjacency list representation of G to file out
void printGraph(FILE *out, Graph G) {
  for (int i = 1; i < ((G->order) + 1); i++) {
    fprintf(out, "%d: ", i);
    printList(out, G->adj[i]);
  }
}
