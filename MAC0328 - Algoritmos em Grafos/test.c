#include <stdio.h>
#include "graph.c"

int main() {
    /* Cria o grafo de exemplo */
    Graph G = GRAPHInit (5);

    /* Insere dois arcos */
    GRAPHInsertArc (G, 0, 1);
    GRAPHInsertArc (G, 1, 2);

    /* Remove um dos arcos */
    GRAPHRemoveArc (G, 1, 2);

    /* Verifica se os vértices 0, 1 e 2 são fontes */
    printf ("Is vertex 0 source? %d\n", GRAPHSource (G, 0));
    printf ("Is vertex 1 source? %d\n", GRAPHSource (G, 1));
    printf ("Is vertex 2 source? %d\n", GRAPHSource (G, 2));

    /* Imprime o grafo */
    GRAPHShow (G);

    return 0;
}
