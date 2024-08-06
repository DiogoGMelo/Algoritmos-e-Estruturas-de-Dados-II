// Raphael Monteiro Consoni Bonaccorsi 12563366
// Diogo Gianezi de Melo 12563522

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

int main () {
    int V;
    scanf("%d", &V);
    Graph *G = initGraph(V);
    int v, w;
    while (scanf("%d %d", &v, &w) != EOF) {
        Arc *arc = (Arc *) malloc(sizeof(Arc));
        arc->v = v; arc->w = w;
        if (arc->v == -1 && arc->w == -1) {
            free(arc);
            break;
        }
        insertArc(G, arc);
        free(arc);
    }
    printGraph(G);
    G = destroyGraph(G);
    
    return 0;
}

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
