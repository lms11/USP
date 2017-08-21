#ifndef GRAPH_BUILDER_H
#define GRAPH_BUILDER_H

#include "graph.h"

/* Constroi grafo complete em θ(V^2) para matriz ou θ(V^3) para listas */
Graph GRAPHbuildComplete (int V);

/* Constroi grafo caminho em θ(V) para matriz ou θ(V^2) para listas */
Graph GRAPHbuildPath (int V);

/* Constroi grafo do rei no xadrez */
Graph GRAPHbuildChessKing (int n);

/* Constroi grafo randomico 1 */
Vertex randV (Graph G);
Graph GRAPHrand1 (int V, int A);

/* Constroi grafo randomico 2 */
Graph GRAPHrand2 (int V, int A);

#endif
