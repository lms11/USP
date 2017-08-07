#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

/* Define a estrutura do grafo */
struct graph {
    int V;
    int A;
    int **adj;
};

/* Construtor: constroi uma matriz AxB com valores iniciais C em θ(AB) */
int ** MATRIXinit (int A, int B, int C)
{
    int ** M = malloc (sizeof (int **) * A);
    int a, b;

    for (a = 0; a < A; a++) {
        M[a] = malloc (sizeof (int *) * B);

        for (b = 0; b < B; b++) {
            M[a][b] = C;
        }
    }

    return M;
}

/* Construtor: cria um grafo de V vértices sem arcos em θ(V^2) */
Graph GRAPHinit (int V)
{
    Graph G = malloc (sizeof * G);
    G->V = V;
    G->A = 0;
    G->adj = MATRIXinit (V, V, 0);
    return G;
}

/* Retorna o número de vértices em θ(1) */
int GRAPHvertex (Graph G)
{
    return G->V;
}

/* Retorna o número de arcos em θ(1) */
int GRAPHarc (Graph G)
{
    return G->A;
}

/*  Método para inserir um arco v-w num grafo em θ(1) */
void GRAPHinsertArc (Graph G, Vertex v, Vertex w)
{
    if (v != w && G->adj[v][w] == 0) {
        G->adj[v][w] = 1;
        G->A++;
    }
}

/* Método para remover um arco em θ(1) */
void GRAPHremoveArc (Graph G, Vertex v, Vertex w)
{
    if (G->adj[v][w] == 1) {
        G->adj[v][w] = 0;
        G->A--;
    }
}

/* Método para verificar se existe o arco v-w em O(1) */
int GRAPHcheckArc (Graph G, Vertex v, Vertex w)
{
    return G->adj[v][w];
}

/* Imprime um grafo em θ(V^2) */
void GRAPHshow (Graph G)
{
    Vertex v, w;
    for (v = 0; v < G->V; v++) {
        printf ("%d: ", v);
        for (w = 0; w < G->V; w++)
            if (G->adj[v][w] == 1)
                printf ("%d ", w);
        printf ("\n");
    }
}

/* Computa o grau de entrada de um vértice v em θ(V) */
int GRAPHindegree (Graph G, Vertex v)
{
    int degree = 0;
    Vertex w;
    for (w = 0; w < G->V; w++) {
        if (G->adj[w][v] == 1)
            degree++;
    }
    return degree;
}

/* Computa o grau de saída de um vértice v em θ(V) */
int GRAPHoutdegree (Graph G, Vertex v)
{
    int degree = 0;
    Vertex w;
    for (w = 0; w < G->V; w++) {
        if (G->adj[v][w] == 1)
            degree++;
    }
    return degree;
}
