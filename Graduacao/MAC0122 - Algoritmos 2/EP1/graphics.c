/***************************************************************/
/**                                                           **/
/**   Luca Tornato Serafini                         9373434   **/
/**   Lucas Moreira Santos                          9345064   **/
/**   Víctor de Sousa Lamarca                       9345922   **/
/**   Exercício-Programa 01                                   **/
/**   Professor:  Fernando Mário de Oliveira Filho            **/
/**   MAC0122 - Princípios de Desenvolvimento de Algoritmos   **/
/**                                                           **/
/***************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <signal.h>
#include "graphics.h"
#include "stack.h"
#include "processor.h"


/*
	Prototypes
*/
int process(Drawing d);

/*
	Definitions of structs
*/
typedef struct circle_struct Circle;
typedef struct line_segment_struct LineSegment;
typedef struct list_struct List;

struct circle_struct {
	double x, y;
	double radius, thickness;
	int filled;
	Circle *next;
} CircleItem;

struct line_segment_struct {
	double x1, y1, x2, y2;
	double thickness;
	int eraseMode;
	LineSegment *next;
} LineSegmentItem;

struct list_struct {
	Circle *circle;
	LineSegment *lineSegment;
	struct list_struct *next;
} ListItem;

struct drawing_struct {
	Stack stack;
	List *firstLayer;
	List *lastLayer;
};


/*
	Implementation
*/

Drawing create_drawing() {
	Drawing d = malloc(sizeof(Drawing));

	d->stack = stack_init();
	d->firstLayer = NULL;
	d->lastLayer = NULL;

	if (!d->stack) {
		free(d);
		return NULL;
	}

	return d;
}

void destroy_list_recursively(List *item) {
	if (item == NULL) return;
	destroy_list_recursively(item->next);
	
	if (item->lineSegment)
		free(item->lineSegment);

	if (item->circle)
		free(item->circle);
	
	free(item);
}

void destroy_drawing(Drawing D) {
	// Destroying circle & line segment lists recursively can be done in O(n)
	destroy_list_recursively(D->firstLayer);

	// Destroy stack
	stack_destroy(D->stack);
	
	// Finally, free the drawing itself
	free(D);
}

int add_line_segment(Drawing D, double x1, double y1, double x2, double y2, double thickness) {
	LineSegment *newSegment = malloc(sizeof(LineSegmentItem));
	if (!newSegment) return 0;

	List *newItem = malloc(sizeof(ListItem));
	if (!newItem) return 0;

	// printf("[DEBUG] Going to create segment.\n{ x1: %lf, y1: %lf, x2: %lf, y2: %lf, thickness: %lf }\n\n", x1, y1, x2, y2, thickness);

	newSegment->x1 = x1;
	newSegment->y1 = y1;
	newSegment->x2 = x2;
	newSegment->y2 = y2;
	newSegment->thickness = thickness < 0 ? -thickness : thickness;
	newSegment->eraseMode = thickness < 0 ? 1 : 0;

	newItem->lineSegment = newSegment;
	newItem->circle = NULL;
	
	if (D->lastLayer)
		D->lastLayer->next = newItem;
	
	D->lastLayer = newItem;

	if (D->firstLayer == NULL)
		D->firstLayer = newItem;

	return 1;
}

int add_circle(Drawing D, double x, double y, double r, double thickness, int filled) {
	Circle *newCircle = malloc(sizeof(CircleItem));
	if (!newCircle) return 0;

	List *newItem = malloc(sizeof(ListItem));
	if (!newItem) return 0;

	// printf("[DEBUG] Going to create circle.\n{ x: %lf, y: %lf, radius: %lf, thickness: %lf, filled: %d }\n\n", x, y, r, thickness, filled);

	newCircle->x = x;
	newCircle->y = y;
	newCircle->radius = r;
	newCircle->thickness = thickness;
	newCircle->filled = filled;

	newItem->lineSegment = NULL;
	newItem->circle = newCircle;
	
	if (D->lastLayer)
		D->lastLayer->next = newItem;
	
	D->lastLayer = newItem;

	if (D->firstLayer == NULL)
		D->firstLayer = newItem;

	return 1;
}

double distance(double x1, double y1, double x2, double y2) {
	return sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
}

/*
	Return the distance a point and a segment
	Point: (x, y)
	Segment from (x1, y1) to (x2, y2)
*/
double distanceBetweenPointAndSegment(double x, double y, double x1, double y1, double x2, double y2) {
    double 	A = x - x1,
    		B = y - y1,
    		C = x2 - x1,
    		D = y2 - y1;
    double prod = A * C + B * D;
    double dist_squared = C * C + D * D;
    double param = -1;
    double X, Y;

    if (dist_squared != 0)
    	param = prod / dist_squared;

    if (param < 0 || (x1 == x2 && y1 == y2)) {
        X = x1;
        Y = y1;
    }
    else if (param > 1) {
        X = x2;
        Y = y2;
    }
    else {
        X = x1 + param * C;
        Y = y1 + param * D;
    }

    return distance(x, y, X, Y);
}

double min(double a, double b) {
	return a < b ? a : b;
}

double max(double a, double b) {
	return a > b ? a : b;
}

int save_pgm(Drawing D, int pix_per_unit, int sample_type, int sample_size, FILE *outfile) {
	List *layer;
	LineSegment *ls;
	Circle *cr;
	double x1 = 0.0, x2 = 0.0, y1 = 0.0, y2 = 0.0, x_ij = 0.0, y_ij = 0.0;
	double dist, val;
	int H, W, i, imax, j, jmax, k, l, n;
	int **matrix, *content;

	if (D->firstLayer == NULL) {
		return EMPTY_IMAGE_ERROR;
	}
	
	layer = D->firstLayer;
	while(layer != NULL) {
		ls = layer->lineSegment;
		cr = layer->circle;

		if (ls != NULL) {
			// Normalize units
			ls->x1			*= pix_per_unit;
			ls->y1			*= pix_per_unit;
			ls->x2			*= pix_per_unit;
			ls->y2			*= pix_per_unit;
			ls->thickness	*= pix_per_unit;

			if ((min(ls->x1, ls->x2) - ls->thickness) < x1)
				x1 = min(ls->x1, ls->x2) - ls->thickness;

			if ((min(ls->y1, ls->y2) - ls->thickness) < y1)
				y1 = min(ls->y1, ls->y2) - ls->thickness;

			if ((max(ls->x1, ls->x2) + ls->thickness) > x2)
				x2 = max(ls->x1, ls->x2) + ls->thickness;

			if ((max(ls->y1, ls->y2) + ls->thickness) > y2)
				y2 = max(ls->y1, ls->y2) + ls->thickness;
		

		} else {
			// Normalize units
			cr->x			*= pix_per_unit;
			cr->y			*= pix_per_unit;
			cr->radius 		*= pix_per_unit;
			cr->thickness 	*= pix_per_unit;

			if (cr->x - cr->radius - cr->thickness < x1)
				x1 = cr->x - cr->radius - cr->thickness;

			if (cr->y - cr->radius - cr->thickness < y1)
				y1 = cr->y - cr->radius - cr->thickness;

			if (cr->x + cr->radius + cr->thickness > x2)
				x2 = cr->x + cr->radius + cr->thickness;

			if (cr->y + cr->radius + cr->thickness > y2)
				y2 = cr->y + cr->radius + cr->thickness;
		

		}

		layer = layer->next;
	}

	W = ceil(x2 - x1);
	H = ceil(y2 - y1);

	matrix = malloc(H * sizeof(int *));
	if (!matrix) {
		printf("Erro ao alocar matriz enquanto tentava salvar o PGM.\n");
		return MEMORY_ERROR;
	}

	content = malloc(H * W * sizeof(int));
	if (!content) {
		printf("Erro ao alocar vetor de conteúdo para a matriz enquanto tentava salvar o PGM.\n");
		return MEMORY_ERROR;
	}

	for (int i = 0; i < H; i++) {
		matrix[i] = &(content[i * W]);

		for (int j = 0; j < W; j++) {
			matrix[i][j] = 255;
		}
	}

	layer = D->firstLayer;
	while(layer != NULL) {
		ls = layer->lineSegment;
		cr = layer->circle;

		if (ls != NULL) {
			ls->x1 -= x1;
			ls->y1 -= y1;
			ls->x2 -= x1;
			ls->y2 -= y1;

			i 		= floor(min(ls->x1, ls->x2) - ls->thickness);
			imax	= floor(max(ls->x1, ls->x2) + ls->thickness);
			jmax	= floor(max(ls->y1, ls->y2) + ls->thickness);

			
			for (; i < imax; i++) {
				for (j = floor(min(ls->y1, ls->y2) - ls->thickness); j < jmax; j++) {
					n = 0;
					
					if (sample_type == GRID_SAMPLE) {
						for (k = 1; k <= sample_size; k++) {
							y_ij = j + 1.0 * k / (sample_size + 1.0);

							for (l = 1; l <= sample_size; l++) {
								x_ij = i + 1.0 * l / (sample_size + 1.0);
								
								dist = distanceBetweenPointAndSegment(x_ij, y_ij, ls->x1, ls->y1, ls->x2, ls->y2);
								printf("Distancia: %lf <= %lf\n", dist, ls->thickness);

								if (dist <= ls->thickness)
									n++;
							}
						}

					} else {
						for (k = 0; k < sample_size; k++) {
							y_ij = j + (double)rand() / (double)((unsigned)RAND_MAX + 1);
							x_ij = i + (double)rand() / (double)((unsigned)RAND_MAX + 1);

							dist = distanceBetweenPointAndSegment(x_ij, y_ij, ls->x1, ls->y1, ls->x2, ls->y2);

							if (dist <= ls->thickness)
								n++;
						}
					}

					/* 	NOTE QUE O MODO BORRACHA FOI INSERIDO POR CONTA PRÓPRIA DOS ALUNOS,
						CONFORME AUTORIZADO PELO PROFESSOR NO ENUNCIADO DO EXERCICIO-PROGRAMA */

					if (ls->eraseMode) {
						if (sample_type == GRID_SAMPLE)
							val = (1.0 * n) / (sample_size * sample_size);
						else
							val = (1.0 * n) / (sample_size);

						matrix[j][i] = floor(max(1.0 * matrix[j][i], 255.0 * val));

					} else {
						if (sample_type == GRID_SAMPLE)
							val = 1.0 - (1.0 * n) / (sample_size * sample_size);
						else
							val = 1.0 - (1.0 * n) / (sample_size);

						matrix[j][i] = floor(min(1.0 * matrix[j][i], 255.0 * val));

					}
					
				}
			}

		} else {
			cr->x -= x1;
			cr->y -= y1;

			i 		= floor(cr->x - cr->thickness - cr->radius);
			imax	= floor(cr->x + cr->thickness + cr->radius);
			jmax	= floor(cr->y + cr->thickness + cr->radius);

			
			for (; i < imax; i++) {
				for (j = floor(cr->y - cr->thickness - cr->radius); j < jmax; j++) {
					n = 0;
					
					if (sample_type == GRID_SAMPLE) {
						for (k = 1; k <= sample_size; k++) {
							y_ij = j + 1.0 * k / (sample_size + 1.0);

							for (l = 1; l <= sample_size; l++) {
								x_ij = i + 1.0 * l / (sample_size + 1.0);
								dist = distance(x_ij, y_ij, cr->x, cr->y);

								if ((cr->filled && dist <= (cr->radius + cr->thickness)) ||
									(!cr->filled && dist >= (cr->radius - cr->thickness) && dist <= (cr->radius + cr->thickness)))
										n++;
							}
						}

					} else {
						for (k = 1; k <= sample_size; k++) {
							y_ij = j + (double)rand() / (double)((unsigned)RAND_MAX + 1);
							x_ij = i + (double)rand() / (double)((unsigned)RAND_MAX + 1);
							dist = distance(x_ij, y_ij, cr->x, cr->y);

							if ((cr->filled && dist <= (cr->radius + cr->thickness)) ||
								(!cr->filled && dist >= (cr->radius - cr->thickness) && dist <= (cr->radius + cr->thickness)))
									n++;
						}
					}

					if (sample_type == GRID_SAMPLE)
						val = 1.0 - (1.0 * n) / (1.0 * sample_size * sample_size);
					else
						val = 1.0 - (1.0 * n) / (1.0 * sample_size);

					matrix[j][i] = floor(min(1.0 * matrix[j][i], 255.0 * val));
				}
			}

		}

		layer = layer->next;
	}

/*
	/* REDEFINIR OS LIMITES DA IMAGEM É NECESSÁRIO DEVIDO A OPERAÇÃO DE BORRACHA/
	for (y1 = 0; y1 < H; y1++) {
		for (j = 0; j < W; j++)
			if (matrix[(int)y1][j] != 255) break;

		if (j < W && matrix[(int)y1][j] != 255) break;
	}

	for (y2 = H - 1; y2 >= 0; y2--) {
		for (j = 0; j < W; j++)
			if (matrix[(int)y2][j] != 255) break;

		if (j < W && matrix[(int)y2][j] != 255) break;
	}

	for (x1 = 0; x1 < W; x1++) {
		for (j = 0; j < H; j++)
			if (matrix[j][(int)x1] != 255) break;

		if (j < H && matrix[j][(int)x1] != 255) break;
	}

	for (x2 = W - 1; x2 >= 0; x2--) {
		for (j = 0; j < H; j++)
			if (matrix[j][(int)x2] != 255) break;

		if (j < H && matrix[j][(int)x2] != 255) break;
	}
*/



	fprintf(outfile, "P2\n");
	fprintf(outfile, "%d %d\n", W, H);
	fprintf(outfile, "255\n");

	for(i = 0; i < H; i++) {
		for (j = 0; j < W; j++) {
			fprintf(outfile, "%d ", matrix[i][j]);
		}
		fprintf(outfile, "\n");
	}

	return 0;
}

