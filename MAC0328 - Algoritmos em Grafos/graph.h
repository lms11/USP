#ifndef GRAPH_H
#define GRAPH_H

#define Vertex int

struct graph;
typedef struct graph * Graph;

/* Construtor: cria um grafo de V vértices sem arcos */
Graph GRAPHinit (int V);

/* Retorna o número de vértices */
int GRAPHvertex (Graph G);

/* Retorna o número de arcos */
int GRAPHarc (Graph G);

/*  Método para inserir um arco v-w num grafo */
void GRAPHinsertArc (Graph G, Vertex v, Vertex w);

/* Método para remover um arco */
void GRAPHremoveArc (Graph G, Vertex v, Vertex w);

/* Método para verificar se existe o arco v-w */
int GRAPHcheckArc (Graph G, Vertex v, Vertex w);

/* Método que verifica se v é fonte */
int GRAPHsource (Graph G, Vertex v);

/* Imprime um grafo */
void GRAPHshow (Graph G);

/* Computa o grau de entrada de um vértice v */
int GRAPHindegree (Graph G, Vertex v);

/* Computa o grau de saída de um vértice v */
int GRAPHoutdegree (Graph G, Vertex v);

/* Verifica se um vértice v é isolado */
int GRAPHisolated (Graph G, Vertex v);

/* Metodo que verifica se v é sorvedouro */
int GRAPHsink (Graph G, Vertex v);

/* Metodo que verifica se G é um torneio */
int GRAPHtournament (Graph G);

/* Metodo que verifica se G é completo */
int GRAPHcomplete (Graph G);

#endif
