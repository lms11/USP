#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "graph_builder.h"

void outputGraphHist (Graph G, char * output) {
    FILE * file = fopen (output, "w");
    if (file == NULL) {
        printf ("Error opening file!\n");
        exit (1);
    }

    Vertex v;
    for (v = 0; v < GRAPHvertex (G); v++)
        fprintf (file, "%d\n", GRAPHindegree(G, v));

    fclose (file);
}

int main (int argc, char **argv) {
    Graph G;

    G = GRAPHrand1 (100, 100);
    outputGraphHist (G, "test_1.in");

    G = GRAPHrand1 (1000, 100);
    outputGraphHist (G, "test_2.in");

    G = GRAPHrand1 (100, 9000);
    outputGraphHist (G, "test_3.in");

    G = GRAPHrand1 (1000, 1000);
    outputGraphHist (G, "test_4.in");

    G = GRAPHrand1 (1000, 5000);
    outputGraphHist (G, "test_5.in");


    return 0;
}
