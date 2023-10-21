Isabella Phung
1702285
Fall 2023
pa3
CSE101
____________
Description:
Program contains List.c, List.h, Graph.c, Graph.h, GraphTest.c, and FindComponents.c 
Contains library of functions for the Graph ADT which uses List ADTs. FindComponents.c is a client program that utilizes the Graph ADT to create graphs from file inputs and uses DFS to find strongly connected components in G.
While I could have created a separate Graph.c file specifically intended for DFS, I believed it might make more sense to instead group DFS and BFS into one library where a user might want to use both.
_____________
Files:
FindComponents.c - main program. Can be opened in any C editor or compiled using gcc with the provided Makefile. Accepts two file names for the input and output files.
List.h - header file for List.c
List.c - implementation of the List ADT library
Graph.h - header file for Graph.c
Graph.c - implementation of the Graph ADT library
GraphTest.c - tester file for the Graph ADT library
Makefile - compiles List.c, Graph.c, GraphTest.c and FindComponents.c. Use via "make" command. Can also perform "make clean" which will remove any object files in the folder and "make format" which will format the .c files according to clang-15's format specifications.
Run code by entering directory and typing "make" command, then typing ./Lex [input filepath] [output filepath]

input files should be in the following format:
[verticies]
[edge origin] [edge termina]
0 0

The Graph ADT has the following functions for accessing and manipulating the ADT:

Constructors-Destructors
Graph newGraph(int n);  //creates a new graph with n verticies
void freeGraph(Graph\* pG); //frees Graph ADT

Access functions
int getOrder(Graph G); //returns order/vertex count
int getSize(Graph G); //returns edge count
int getParent(Graph G, int u); //returns parent of vertex u in G if DFS has been called
int getDiscover(Graph G, int u); //returns discovery time of vertex u in G if DFS has been called
int getFinish(Graph G, int u); //returns finish time of vertex u in G if DFS has been called
int getSource(Graph G); //returns recent source vertex if BFS has been called
int getParent(Graph G, int u); //returns u's parent vertex if DFS or BFS has been called
int getDist(Graph G, int u); //returns distance between source and u if BFS has been called
void getPath(List L, Graph G, int u); //returns shortest path between source and u if BFS has been called
 
Manipulation procedures 
void makeNull(Graph G); //removes all edges in G
void addEdge(Graph G, int u, int v); //adds undirected edge between u and v
void addArc(Graph G, int u, int v); //adds directed edge from u to v
void BFS(Graph G, int s); //performs BFS on graph with given source
void DFS(Graph G, List s); //runs DFS algorithm following order from List S

Other operations
Graph transpose(Graph G); //returns transpose of given Graph G
Graph copyGraph(Graph G); //returns copy of given Graph G
void printGraph(FILE\* out, Graph G); //prints Graph in adjacency list format
