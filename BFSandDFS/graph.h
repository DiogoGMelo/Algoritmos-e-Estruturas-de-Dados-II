#ifndef graph_h
#define graph_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int V;
    int A;
    int *adj;
} Graph;

typedef struct {
    int v;
    int w;
} Arc;

Graph* initGraph(int n);
Graph* destroyGraph(Graph *G);
int insertArc(Graph *G, Arc *arc);
int printGraph(Graph *G);
int DFS(Graph *G, int v, int *visited);
int BFS(Graph *G, int v, int *visited);

#endif