#include <time.h>
#include <stdio.h>
#include "graph_builder.h"

double sw (int V, int A) {
    clock_t begin = clock();
    GRAPHrand1 (V, A);
    clock_t end = clock();
    return (double)(end - begin) / CLOCKS_PER_SEC;
}

int main (int argc, char **argv) {
    /* Se tiver mais de um argumento, ele executa os testes automáticos */
    /* do contrário, ele pergunta o V e o A. */

    if (argc > 1) {
        printf ("Rodando testes:\n");
        printf ("V = 10000, A = 10000  => %lf\n",   sw (10000,    10000));
        printf ("V = 10000, A = 100000 => %lf\n",   sw (10000,   100000));
        printf ("V = 10000, A = 1000000 => %lf\n",  sw (10000,  1000000));
        printf ("V = 10000, A = 10000000 => %lf\n", sw (10000, 10000000));
        printf ("V = 10000, A = 50000000 => %lf\n", sw (10000, 50000000));
        printf ("V = 10000, A = 95000000 => %lf\n", sw (10000, 95000000));
        printf ("V = 10000, A = 99000000 => %lf\n", sw (10000, 99000000));

    } else {
        int V, A;
        printf ("V = ");
        scanf ("%d", &V);
        printf ("A = ");
        scanf ("%d", &A);

        printf ("\nConstruindo grafo...\n");
        Graph G = GRAPHrand1 (V, A);
        GRAPHshow (G);
    }

    return 0;
}
