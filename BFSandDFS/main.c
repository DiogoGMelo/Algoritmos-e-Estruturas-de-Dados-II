// Raphael Monteiro Consoni Bonaccorsi 12563366
// Diogo Gianezi de Melo 12563522

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

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
    printf("DFS\n");
    DFS(G, 0, (int *) calloc(V, sizeof(int)));
    BFS(G, 0, (int *) calloc(V, sizeof(int)));
    G = destroyGraph(G);
    
    return 0;
}