#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

/* Define a estrutura de um nó */
struct node {
    Vertex w;
    struct node * next;
};
typedef struct node * link;

/* Define a estrutura do grafo */
struct graph {
    int V;
    int A;
    link *adj;
};

/* Construtor: constroi um novo nó */
link NODEinit (Vertex w, link first)
{
    link p = malloc (sizeof * p);
    p->w = w;
    p->next = first;
    return p;
}

/* Construtor: cria um grafo de V vértices sem arcos em θ(V) */
Graph GRAPHinit (int V)
{
    Vertex v;
    Graph G = malloc (sizeof * G);
    G->V = V;
    G->A = 0;
    G->adj = malloc (V * sizeof (link));
    for (v = 0; v < V; v++)
        G->adj[v] = NULL;
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

/*  Método para inserir um arco v-w num grafo em O(V) */
void GRAPHinsertArc (Graph G, Vertex v, Vertex w)
{
    link p;
    if (v != w) {
        for (p = G->adj[v]; p != NULL; p = p->next)
            if (p->w == w) return;

        G->adj[v] = NODEinit (w, G->adj[v]);
        G->A++;
    }
}

/* Método para remover um arco em O(V) */
void GRAPHremoveArc (Graph G, Vertex v, Vertex w)
{
    link ant, p;
    for (ant = NULL, p = G->adj[v]; p != NULL && p->w != w; ant = p, p = p->next);
    if (p != NULL) {
        if (ant == NULL)
            G->adj[v] = p->next;
        else
            ant->next = p->next;

        G->A--;
        free (p);
    }
}

/* Método para verificar se existe o arco v-w em O(V) */
int GRAPHcheckArc (Graph G, Vertex v, Vertex w)
{
    link p;
    for (p = G->adj[v]; p != NULL && p->w != w; p = p->next);
    if (p != NULL)
        return 1;
    else
        return 0;
}

/* Imprime um grafo em θ(V+A) */
void GRAPHshow (Graph G)
{
    Vertex v;
    link p;
    for (v = 0; v < G->V; v++) {
        printf ("%d: ", v);
        for (p = G->adj[v]; p != NULL; p = p->next)
            printf ("%d ", p->w);
        printf ("\n");
    }
}

/* Computa o grau de entrada de um vértice v em O(V+A) */
int GRAPHindegree (Graph G, Vertex v)
{
    int degree = 0;
    Vertex w;
    link p;
    for (w = 0; w < G->V; w++) {
        if (v == w)
            continue;

        for (p = G->adj[w]; p != NULL; p = p->next) {
            if (p->w == v) {
                degree++;
                break;
            }
        }
    }

    return degree;
}

/* Computa o grau de saída de um vértice v em O(V) */
int GRAPHoutdegree (Graph G, Vertex v)
{
    int degree = 0;
    link p;
    for (p = G->adj[v]; p != NULL; p = p->next, degree++);
    return degree;
}
