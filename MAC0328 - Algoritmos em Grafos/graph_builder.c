#include <stdlib.h>
#include "graph_builder.h"

/* Constroi grafo complete em θ(V^2) para matriz ou θ(V^3) para listas */
Graph GRAPHbuildComplete (int V)
{
    Graph G = GRAPHinit (V);
    Vertex v, w;
    for (v = 0; v < V; v++)
        for (w = 0; w < V; w++)
            GRAPHinsertArc (G, v, w);
    return G;
}

/* Constroi grafo caminho em θ(V) para matriz ou θ(V^2) para listas */
Graph GRAPHbuildPath (int V)
{
    Graph G = GRAPHinit (V);
    Vertex v;
    for (v = 0; v < V - 1; v++)
        GRAPHinsertArc (G, v, v + 1);
    return G;
}

/* Constroi grafo do rei no xadrez */
Graph GRAPHbuildChessKing (int n)
{
    Graph G = GRAPHinit (n * n);
    Vertex l, c, i, j;
    Vertex v;
    for (v = 0; v < n * n; v++) {
        l = v / n; // Linha do vértice atual
        c = v % n; // Coluna do vértice atual
        for (i = l - 1; i <= l + 1; i++)
            for (j = c - 1; j <= c + 1; j++)
                if (i >= 0 && i < n && j >= 0 && j < n)
                    GRAPHinsertArc (G, v, i * n + j);
    }
    return G;
}

/* Constroi grafo randomico 1 */
Vertex randV (Graph G)
{
    double r = rand () / (RAND_MAX + 1.0);
    return r * GRAPHvertex (G);
}

Graph GRAPHrand1 (int V, int A)
{
    Graph G = GRAPHinit (V);
    Vertex v, w;
    while (GRAPHarc (G) != A) {
        v = randV (G);
        w = randV (G);
        GRAPHinsertArc (G, v, w);
    }
    return G;
}

/* Constroi grafo randomico 2 */
Graph GRAPHrand2 (int V, int A)
{
    Graph G = GRAPHinit (V);
    Vertex v, w;
    double p = (double) A / (V * (V - 1));
    for (v = 0; v < V; v++)
        for (w = 0; w < V; w++)
            if (rand() < p * (RAND_MAX + 1.0))
                GRAPHinsertArc (G, v, w);
    return G;
}
