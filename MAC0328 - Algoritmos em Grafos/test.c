#include <stdio.h>
#include "test.h"
#include "graph.h"

int tests_run = 0;

static char * test_arc (Graph G, Vertex v, Vertex w, int expected) {
    mu_assert ("error, arc didn't pass", GRAPHcheckArc (G, v, w) == expected);
    return 0;
}

static char * test_vertex_source (Graph G, Vertex v, int expected) {
    mu_assert ("error, vertex is not a source", GRAPHsource (G, v) == expected);
    return 0;
}

static char * test_vertex_sink (Graph G, Vertex v, int expected) {
    mu_assert ("error, vertex is not a sink", GRAPHsink (G, v) == expected);
    return 0;
}

static char * test_vertex_indegree (Graph G, Vertex v, int expected) {
    mu_assert ("error, vertex indegree is wrong", GRAPHindegree (G, v) == expected);
    return 0;
}

static char * test_vertex_outdegree (Graph G, Vertex v, int expected) {
    mu_assert ("error, vertex outdegree is wrong", GRAPHoutdegree (G, v) == expected);
    return 0;
}

static char * test_vertex_isolated (Graph G, Vertex v, int expected) {
    mu_assert ("error, vertex is not isolated", GRAPHisolated (G, v) == expected);
    return 0;
}

static char * test_graph_tournament (Graph G, int expected) {
    mu_assert ("error, grapg is not tournament", GRAPHtournament (G) == expected);
    return 0;
}

static char * test_graph_complete (Graph G, int expected) {
    mu_assert ("error, grapg is not complete", GRAPHcomplete (G) == expected);
    return 0;
}

static char * all_tests (Graph G) {
    Vertex v, w;

    /* Insere dois arcos e testa */
    GRAPHinsertArc (G, 0, 1);
    mu_run_test (test_arc, G, 0, 1, 1);
    GRAPHinsertArc (G, 1, 2);
    mu_run_test (test_arc, G, 1, 2, 1);

    /* Remove um dos arcos */
    GRAPHremoveArc (G, 1, 2);
    mu_run_test (test_arc, G, 1, 2, 0);

    /* Testa propriedade dos vértices */
    mu_run_test (test_vertex_source, G, 0, 1);
    mu_run_test (test_vertex_source, G, 1, 0);
    mu_run_test (test_vertex_sink, G, 0, 0);
    mu_run_test (test_vertex_sink, G, 1, 1);
    mu_run_test (test_vertex_indegree, G, 0, 0);
    mu_run_test (test_vertex_indegree, G, 1, 1);
    mu_run_test (test_vertex_outdegree, G, 0, 1);
    mu_run_test (test_vertex_outdegree, G, 1, 0);
    mu_run_test (test_vertex_isolated, G, 0, 0);
    mu_run_test (test_vertex_isolated, G, 1, 0);
    mu_run_test (test_vertex_isolated, G, 2, 1);

    /* Testa a propriedade do grafo */
    mu_run_test (test_graph_tournament, G, 0);
    mu_run_test (test_graph_complete, G, 0);

    /* Torna o grafo um torneio */
    for (v = 0; v < GRAPHvertex (G); v++)
        for (w = v + 1; w < GRAPHvertex (G); w++)
            GRAPHinsertArc (G, v, w);

    /* Verifica se é torneio */
    mu_run_test (test_graph_tournament, G, 1);

    /* Torna o grafo completo */
    for (v = 0; v < GRAPHvertex (G); v++)
        for (w = 0; w < GRAPHvertex (G); w++)
            GRAPHinsertArc (G, v, w);

    /* Verifica se é completo */
    mu_run_test (test_graph_complete, G, 1);

    return 0;
}

int main() {
    /* Cria o grafo de exemplo */
    Graph G = GRAPHinit (5);

    /* Executa os testes */
    char * result = all_tests (G);
    if (result != 0)
        printf ("%s\n", result);
    else
        printf ("All tests passed! \\o/\n");

    printf("Tests run: %d\n\n", tests_run);

    /* Imprime o grafo */
    GRAPHshow (G);

    return result != 0;
}
