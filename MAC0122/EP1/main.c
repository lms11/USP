#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "processor.h"
#include "graphics.h"

// test case: 
// test_in2.fig output.pgm 60 grid 3

int main(int argc, char **argv) {
	Drawing draw = create_drawing();
	FILE *in, *out;
	int res, sample_type;

	if (argc < 6) {
		printf("usage: draw <infile> <outfile> <pix_per_unit> <sample_type> <sample_size>\n\n");
		printf("- infile -- input file.\n");
		printf("- outfile -- output file.\n");
		printf("- pix_per_unit -- number of pixels per unit.\n");
		printf("- sample_type -- either 'grid', for uniform grid, or 'random' for random sample.\n");
		printf("- sample_size -- size of sample.\n\n");

		printf("operations available:");
		for(int x = 0; x < N_OPS_AVAILABLE; x++) printf(" %s", OPS_AVAILABLE[x]);

		printf("\n\neaster egg: try to generate an image from google.fig\n");

		return 0;
	}

	if (!draw) {
		printf("Erro ao alocar novo desenho. Terminando o programa.\n");
		exit(0);
	}

	// in = fopen(argv[1], "r");
	in = fopen(argv[1], "r");
	if (!in) {
		printf("Erro ao abrir arquivo de entrada. Terminando o programa.\n");
		exit(0);
	}

	// out = fopen(argv[2], "rw");
	out = fopen(argv[2], "w");
	if (!out) {
		printf("Erro ao abrir arquivo de saida. Terminando o programa.\n");
		exit(0);
	}

	res = processInput(draw, in);

	if (res >= PROCESSOR_ERROR_UNKNOWN) {
		printf("Erro ao processar arquivo de entrada. Terminando o programa.\n");
		exit(0);
	}

	sample_type = (strcmp(argv[4], "grid") == 0) ? GRID_SAMPLE : RANDOM_SAMPLE;
	res = save_pgm(draw, atoi(argv[3]), sample_type, atoi(argv[5]), out);

	if (res >= 1) {
		switch (res) {
			case 1:
				printf("A imagem está vazia (não há nenhum segmento ou circulo). Terminando o programa.\n");;
				break;
			case 2:
				printf("Erro ao alocar memória. Terminando o programa.\n");
				break;
			default:
				printf("Erro desconhecido. Terminando o programa.\n");
				break;
		}

		exit(0);
	}

	fclose(in);
	fclose(out);

	return 0;
}