// Raphael Monteiro Consoni Bonaccorsi 12563366
// Diogo Gianezi de Melo 12563522

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

Graph* initGraph(int n) {
    Graph *G = (Graph *) malloc(sizeof(Graph));
    G->V = n;
    G->A = 0;
    G->adj = (int *) malloc(n * n * sizeof(int));
    for (int i = 0; i < n * n; i++) {
        G->adj[i] = 0;
    }
    return G;
}

Graph* destroyGraph(Graph *G) {
    free(G->adj);
    free(G);
    return NULL;
}

int insertArc(Graph *G, Arc *arc) {
    if (arc->v >= 0 && arc->v < G->V && arc->w >= 0 && arc->w < G->V) {
        G->adj[arc->v * G->V + arc->w] = 1;
        G->adj[arc->w * G->V + arc->v] = 1;
        G->A++;
    }
    return 0;
}

int printGraph(Graph *G) {
    printf("Total of vertices: %d, total of arcs: %d\n", G->V, G->A);
    for (int i = 0; i < G->V; i++) {
        printf("Vertex %d, arcs: ", i);
        int flag = 0;
        for (int j = 0; j < G->V; j++) {
            if (G->adj[i * G->V + j] == 1) {
                if (flag) {
                    printf(", ");
                }
                flag = 1;
                printf("%d", j);
            }
        }
        printf("\n");
    }
    return 0;
}

int DFS(Graph *G, int v, int *visited) {
    visited[v] = 1;
    printf("visited %d\n", v);
    for (int i = 0; i < G->V; i++) {
        if (G->adj[v * G->V + i] == 1 && !visited[i]) {
            DFS(G, i, visited);
        }
    }
    return 0;
}

int BFS(Graph *G, int v, int *visited) {
    int queue[G->V];
    int front = 0, rear = 0;
    queue[rear++] = v;
    visited[v] = 1;
    printf("BFS\n");
    while (front < rear) {
        v = queue[front++];
        printf("visited %d\n", v);
        for (int i = 0; i < G->V; i++) {
            if (G->adj[v * G->V + i] == 1 && !visited[i]) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }
    }
    return 0;
}