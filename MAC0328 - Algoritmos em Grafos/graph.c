#import <stdlib.h>

#define Vertex int

struct graph {
    int V;
    int A;
    int **adj;
};
typedef struct graph * Graph;

/* Construtor: constroi uma matriz AxB com valores iniciais C em θ(AB) */
int ** MATRIXInit (int A, int B, int C)
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
Graph GRAPHInit (int V)
{
    Graph G = malloc (sizeof * G);
    G->V = V;
    G->A = 0;
    G->adj = MATRIXInit(V, V, 0);
    return G;
}

/*  Método para inserir um arco v-w num grafo em θ(1) */
void GRAPHInsertArc (Graph G, Vertex v, Vertex w)
{
    if (v != w && G->adj[v][w] == 0) {
        G->adj[v][w] = 1;
        G->A++;
    }
}

/* Método para remover um arco em θ(1) */
void GRAPHRemoveArc (Graph G, Vertex v, Vertex w)
{
    if (G->adj[v][w] == 1) {
        G->adj[v][w] = 0;
        G->A--;
    }
}

/* Método que verifica se v é fonte em θ(V) */
int GRAPHSource (Graph G, Vertex v)
{
    Vertex u = 0;
    for (u = 0; u < G->V; u++) {
        if (G->adj[u][v] == 1)
            return 0;
    }
    return 1;
}

/* Imprime um grafo em θ(V^2) */
void GRAPHShow (Graph G)
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
