#include "graph.h"

/* Verifica se um vértice v é isolado em θ(V) para matriz ou O(V+A) para listas */
int GRAPHisolated (Graph G, Vertex v)
{
    if (GRAPHindegree (G, v) == 0 && GRAPHoutdegree (G, v) == 0)
        return 1;
    else
        return 0;
}

/* Método que verifica se v é fonte em θ(V) para matriz ou O(V) para listas */
int GRAPHsource (Graph G, Vertex v)
{
    if (GRAPHindegree (G, v) == 0)
        return 1;
    else
        return 0;
}

/* Metodo que verifica se v é sorvedouro em θ(V) para matriz ou O(V) para listas */
int GRAPHsink (Graph G, Vertex v)
{
    if (GRAPHoutdegree (G, v) == 0)
        return 1;
    else
        return 0;
}

/* Metodo que verifica se G é um torneio em O(V^2) para matriz ou O(V^3) para listas */
int GRAPHtournament (Graph G)
{
    Vertex v, w;
    for (v = 0; v < GRAPHvertex (G); v++)
        for (w = 0; w < GRAPHvertex (G); w++)
            if (v == w)
                continue;
            else if ((GRAPHcheckArc (G, v, w) ^ GRAPHcheckArc (G, w, v)) == 0)
                return 0;
    return 1;
}

/* Metodo que verifica se G é completo em θ(1) */
int GRAPHcomplete (Graph G)
{
    if (GRAPHarc (G) == (GRAPHvertex (G) * (GRAPHvertex (G) - 1)))
        return 1;
    else
        return 0;
}
