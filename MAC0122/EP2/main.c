#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "graphics.h"
#include "builder.h"

int main(int argc, char **argv) {
	char algorithm[20], sample_type[7], outfile[200];
	int num_elements = 0, pixels_per_unit = 0, sample_size = 0;
	double scale_x = 0.0, scale_y = 0.0, thickness = 0.0;
	int ss;
	FILE *out;

	if (argc < 9) {
		printf("uso: tree <algoritmo> <num_elementos> <outfile> <scale_x> <scale_y> <grossura> <pix_por_unidade> <tamanho_amostra> <tipo_amostra>\n\n");
		printf("- algoritmo -- qual algoritmo a árvore deve representar. Disponivel: qsort, selection_sort, insertion_sort, bubble_sort, quicksort_random, quicksort, mergesort, heapsort.\n");
		printf("- num_elementos -- (número inteiro) número de elementos para ser sorteado. Tenha cuidado: evite escolher números altos (o programa ainda funcionará, mas seu tempo de execução cresce rapidamente).\n");
		printf("- outfile -- nome do arquivo de saída que a imagem deve ser escrita.\n");
		printf("- scale_x -- (número real) fator escalar na largura (eixo X).\n");
		printf("- scale_y -- (número real) fator escalar na vertical (eixo Y).\n");
		printf("- grossura -- (número real) grossura das linhas e dos nós.\n");
		printf("- pix_por_unidade -- (número inteiro) número de pixels por unidade.\n");
		printf("- tamanho_amostra -- (número inteiro) tamanho da amostra.\n");
		printf("- tipo_amostra -- (opcional) 'grid', para um gride uniforme, ou 'random' para um grid rândomico. Grid por padrão.\n\n");
		return 0;

	} else {
		strcpy(algorithm, argv[1]);
		num_elements = atoi(argv[2]);
		strcpy(outfile, argv[3]);
		scale_x = atof(argv[4]);
		scale_y = atof(argv[5]);
		thickness = atof(argv[6]);
		pixels_per_unit = atoi(argv[7]);
		sample_size = atoi(argv[8]);
		
		if (argc >= 9) {
			strcpy(sample_type, argv[9]);
		
		} else {
			strcpy(sample_type, "grid");

		}

	}

	out = fopen(outfile, "w");
	if (!out) {
		printf("Erro ao abrir arquivo de saida. Terminando o programa.\n");
		exit(0);
	}

	ss = (strcmp(sample_type, "grid") == 0) ? GRID_SAMPLE : RANDOM_SAMPLE;
	Node *root = process(algorithm, num_elements);
	Drawing draw = create_drawing();
	build(draw, root, scale_x, scale_y, thickness);
	save_pgm(draw, pixels_per_unit, ss, sample_size, out);


	return 0;
}