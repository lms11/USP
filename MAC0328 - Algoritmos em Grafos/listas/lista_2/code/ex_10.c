#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define Vertex int

struct graph {
    int V;
    int A;
    int **adj;
};
typedef struct graph * Graph;

struct uf {
    int *parent;
    int *size;
    int count;
};
typedef struct uf * UF;

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

/* Destrutor: destroi a matriz dada */
void MATRIXdestroy (int ** M, int A)
{
    for (int a = 0; a < A; a++)
        free (M[a]);
    free (M);
}

/* Construtor: constroi uma UF com N conjuntos */
UF UFinit (int N)
{
    UF uf = malloc (sizeof * uf);
    uf->count = N;
    uf->size = malloc (N * sizeof (int));
    uf->parent = malloc (N * sizeof (int));

    for (int i = 0; i < N; i++) {
        uf->size[i] = 1;
        uf->parent[i] = i;
    }

    return uf;
}

/* Destrutor: destroi a matriz dada */
void UFdestroy (UF uf)
{
    free (uf->size);
    free (uf->parent);
    free (uf);
}

/*  Método para inserir um arco v-w num grafo em θ(1) */
void GRAPHinsertArc (Graph G, Vertex v, Vertex w)
{
    if (v != w && G->adj[v][w] == 0) {
        G->adj[v][w] = 1;
        G->A++;
    }
}

/* Construtor: cria um grafo de V vértices sem arcos em θ(V^2) */
Graph GRAPHinit (int V, int E)
{
    Graph G = malloc (sizeof * G);
    G->V = V;
    G->A = 0;
    G->adj = MATRIXinit (V, V, 0);
    double p_e = 2.0 * E / (V*(V-1));
    Vertex u, v;
    srand (time (NULL));
    for (u = 0; u < V; u++)
        for (v = u + 1; v < V; v++)
            if (rand() < p_e * (RAND_MAX + 1.0)) {
                GRAPHinsertArc (G, u, v);
                GRAPHinsertArc (G, v, u);
            }
    return G;
}

/* Destrutor do grafo */
void GRAPHdestroy (Graph G)
{
    MATRIXdestroy (G->adj, G->V);
}

/* Operação de find do Union-Find */
int findOp (UF uf, int u)
{
    if (u != uf->parent[u])
        uf->parent[u] = findOp (uf, uf->parent[u]);
    return uf->parent[u];
}

/* Operação de união do Union-Find */
void unionOp (UF uf, int u, int v)
{
    int i = findOp (uf, u);
    int j = findOp (uf, v);
    if (i != j) {
        if (uf->size[i] < uf->size[j]) {
            uf->parent[i] = j;
            uf->size[j] += uf->size[i];
        } else {
            uf->parent[j] = i;
            uf->size[i] += uf->size[j];
        }
        uf->count--;
    }
}

/* Main */
int main ()
{
    UF uf;
    int V[5] = { 10, 50, 100, 1000, 10000 };
    int i, v, e, e_max, reachable, pairs;
    double p;
    Vertex u, w;

    printf("vértices,arestas,probabilidade,componentes\n");

    for (i = 0; i < 5; i++) {
        v = V[i]; // Número de vértices
        e_max = v * (v-1) / 2;
        uf = UFinit (v);

        for (e = 0; e <= e_max; e++) {
            // Cria um grafo G com configurações {v, e}
            Graph G = GRAPHinit (v, e);

            // Monta a UF
            for (u = 0; u < G->V; u++)
                for (v = 0; v < G->V; v++)
                    if (G->adj[u][v] == 1)
                        unionOp (uf, u, v);

            // Conta o número de pares que são alcançaveis
            reachable = 0;
            pairs = 0;
            for (u = 0; u < G->V; u++)
                for (w = u + 1; w < G->V; w++) {
                    pairs++;
                    if (findOp (uf, u) == findOp (uf, w))
                        reachable++;
                }

            // Calcula a probabilidade p
            p = 1.0 * reachable / pairs;

            // Imprime no formato CSV
            printf ("%d;%d;%lf;%d\n", v, e, p, uf->count);

            // Break if p = 1 is reached
            if (1 - p <= 1e-6)
                break;

            // Destroi as memorias alocadas
            GRAPHdestroy (G);
        }

        free (uf);
    }

    return 0;
}
