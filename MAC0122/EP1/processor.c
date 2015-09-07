#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "processor.h"

typedef struct circle_struct *Circle;
typedef struct line_segment_struct *LineSegment;

struct drawing_struct {
	Stack stack;
	Circle *circle;
	LineSegment *lineSegment;
};

int processInput(Drawing d, FILE *input) {
	double value = 0;
	int res = 0;
	char string[100];

	while (fscanf(input, " %s", string) != EOF) {
		if (sscanf(string, " %lf", &value)) {
			res = stack_push(d->stack, value);
			
		} else {
			res = processOperator(d, string);

		}

		if (res != PROCESSOR_SUCCESS && res != 1)
			return res;
	}

	return PROCESSOR_SUCCESS;
}


int processOperator(Drawing d, char *op) {
	int res = 0;

	// Look for which operator it is and then process it
	for (int i = 0; i < N_OPS_AVAILABLE; i++) {
		if (strlen(op) == strlen(OPS_AVAILABLE[i]) && strcmp(op, OPS_AVAILABLE[i]) == 0) {
			switch (i) {
				case 0:
					res = process_sum(d->stack);
					break;
				case 1:
					res = process_subtraction(d->stack);
					break;
				case 2:
					res = process_multiplication(d->stack);
					break;
				case 3:
					res = process_division(d->stack);
					break;
				case 4:
					res = process_pi(d->stack);
					break;
				case 5:
					res = process_sin(d->stack);
					break;
				case 6:
					res = process_cos(d->stack);
					break;
				case 7:
					res = process_deg(d->stack);
					break;
				case 8:
					res = process_cm(d->stack);
					break;
				case 9:
					res = process_mm(d->stack);
					break;
				case 10:
					res = process_pt(d->stack);
					break;
				case 11:
					res = process_copy(d->stack);
					break;
				case 12:
					res = process_translate(d->stack);
					break;
				case 13:
					res = process_mtranslate(d->stack);
					break;
				case 14:
					res = process_rotate(d->stack);
					break;
				case 15:
					res = process_mrotate(d->stack);
					break;
				case 16:
					res = process_line(d);
					break;
				case 17:
					res = process_circle(d);
					break;
				case 18:
					res = process_fillcircle(d);
					break;
				case 19:
					res = process_show(d->stack);
					break;
				case 20:
					res = process_tan(d->stack);
					break;
				case 21:
					res = process_arcsin(d->stack);
					break;
				case 22:
					res = process_arccos(d->stack);
					break;
				case 23:
					res = process_arctan(d->stack);
					break;
				case 24:
					res = process_eraseline(d);
					break;
				case 25:
					res = process_e(d->stack);
					break;
				case 26:
					res = process_lg(d->stack);
					break;
				case 27:
					res = process_ln(d->stack);
					break;
				case 28:
					res = process_log(d->stack);
					break;
				case 29:
					res = process_abs(d->stack);
					break;
				default:
					res = throw_error(op, PROCESSOR_ERROR_ILEGAL_OP);
					break;
			}

			break;
		}
	}

	return res;
}

int throw_error(char *error, PROCESSOR_RESULT result) {
	printf("Erro na operação \"%s\": %s", 
		result == PROCESSOR_ERROR_ILEGAL_OP ? "operação ilegal" : OPS_AVAILABLE[result - PROCESSOR_ERROR_SUM], 
		error);
	return result;
}

int process_sum(Stack s) {
	double a, b;
	if (stack_size(s) < 2) {
		return throw_error("Impossivel realizar operação. Motivo: há menos elementos na pilha do que o necessário (stack underflow).\n", PROCESSOR_ERROR_SUM);
	}
	
	b = stack_pop(s);
	a = stack_pop(s);

	if (!stack_push(s, a + b)) {
		return throw_error("Impossivel realizar operação. Motivo: não foi possivel inserir novos elementos na memória (erro de alocamento de memória).\n", PROCESSOR_ERROR_SUM);
	}

	return PROCESSOR_SUCCESS;
}

int process_subtraction(Stack s) {
	double a, b;
	if (stack_size(s) < 2) {
		return throw_error("Impossivel realizar operação. Motivo: há menos elementos na pilha do que o necessário (stack underflow).\n", PROCESSOR_ERROR_SUBTRACTION);
	}
	
	b = stack_pop(s);
	a = stack_pop(s);

	if (!stack_push(s, a - b)) {
		return throw_error("Impossivel realizar operação. Motivo: não foi possivel inserir novos elementos na memória (erro de alocamento de memória).\n", PROCESSOR_ERROR_SUBTRACTION);
	}

	return PROCESSOR_SUCCESS;
}

int process_multiplication(Stack s) {
	double a, b;
	if (stack_size(s) < 2) {
		return throw_error("Impossivel realizar operação. Motivo: há menos elementos na pilha do que o necessário (stack underflow).\n", PROCESSOR_ERROR_MULTIPLICATION);
	}
	
	b = stack_pop(s);
	a = stack_pop(s);

	if (!stack_push(s, a * b)) {
		return throw_error("Impossivel realizar operação. Motivo: não foi possivel inserir novos elementos na memória (erro de alocamento de memória).\n", PROCESSOR_ERROR_MULTIPLICATION);
	}

	return PROCESSOR_SUCCESS;
}

int process_division(Stack s) {
	double a, b;
	if (stack_size(s) < 2) {
		return throw_error("Impossivel realizar operação. Motivo: há menos elementos na pilha do que o necessário (stack underflow).\n", PROCESSOR_ERROR_DIVISION);
	}
	
	b = stack_pop(s);
	a = stack_pop(s);

	if (!stack_push(s, a / b)) {
		return throw_error("Impossivel realizar operação. Motivo: não foi possivel inserir novos elementos na memória (erro de alocamento de memória).\n", PROCESSOR_ERROR_DIVISION);
	}

	return PROCESSOR_SUCCESS;
}

int process_pi(Stack s) {
	if (!stack_push(s, CONST_PI)) {
		return throw_error("Impossivel realizar operação. Motivo: não foi possivel inserir novos elementos na memória (erro de alocamento de memória).\n", PROCESSOR_ERROR_PI);
	}

	return PROCESSOR_SUCCESS;
}

int process_sin(Stack s) {
	double a;
	if (stack_size(s) < 1) {
		return throw_error("Impossivel realizar operação. Motivo: há menos elementos na pilha do que o necessário (stack underflow).\n", PROCESSOR_ERROR_SIN);
	}

	a = stack_pop(s);
	
	if (!stack_push(s, sin(a))) {
		return throw_error("Impossivel realizar operação. Motivo: não foi possivel inserir novos elementos na memória (erro de alocamento de memória).\n", PROCESSOR_ERROR_SIN);
	}

	return PROCESSOR_SUCCESS;
}

int process_cos(Stack s) {
	double a;
	if (stack_size(s) < 1) {
		return throw_error("Impossivel realizar operação. Motivo: há menos elementos na pilha do que o necessário (stack underflow).\n", PROCESSOR_ERROR_COS);
	}

	a = stack_pop(s);
	
	if (!stack_push(s, cos(a))) {
		return throw_error("Impossivel realizar operação. Motivo: não foi possivel inserir novos elementos na memória (erro de alocamento de memória).\n", PROCESSOR_ERROR_COS);
	}

	return PROCESSOR_SUCCESS;
}

int process_deg(Stack s) {
	double a;
	if (stack_size(s) < 1) {
		return throw_error("Impossivel realizar operação. Motivo: há menos elementos na pilha do que o necessário (stack underflow).\n", PROCESSOR_ERROR_DEG);
	}

	a = stack_pop(s);
	
	if (!stack_push(s, (2 * CONST_PI * a / 360.0) )) {
		return throw_error("Impossivel realizar operação. Motivo: não foi possivel inserir novos elementos na memória (erro de alocamento de memória).\n", PROCESSOR_ERROR_DEG);
	}

	return PROCESSOR_SUCCESS;
}

int process_cm(Stack s) {
	if (stack_size(s) < 1) {
		return throw_error("Impossivel realizar operação. Motivo: há menos elementos na pilha do que o necessário (stack underflow).\n", PROCESSOR_ERROR_CM);
	}

	return PROCESSOR_SUCCESS;
}

int process_mm(Stack s) {
	double a;
	if (stack_size(s) < 1) {
		return throw_error("Impossivel realizar operação. Motivo: há menos elementos na pilha do que o necessário (stack underflow).\n", PROCESSOR_ERROR_MM);
	}

	a = stack_pop(s);
	
	if (!stack_push(s, (0.1 * a) )) {
		return throw_error("Impossivel realizar operação. Motivo: não foi possivel inserir novos elementos na memória (erro de alocamento de memória).\n", PROCESSOR_ERROR_MM);
	}

	return PROCESSOR_SUCCESS;
}

int process_pt(Stack s) {
	double a;
	if (stack_size(s) < 1) {
		printf("Tamanho da stack: %d. %p\n", stack_size(s), s);
		return throw_error("Impossivel realizar operação. Motivo: há menos elementos na pilha do que o necessário (stack underflow).\n", PROCESSOR_ERROR_PT);
	}

	a = stack_pop(s);
	
	if (!stack_push(s, (CONST_PT * a) )) {
		return throw_error("Impossivel realizar operação. Motivo: não foi possivel inserir novos elementos na memória (erro de alocamento de memória).\n", PROCESSOR_ERROR_PT);
	}

	return PROCESSOR_SUCCESS;
}

int copy_recursively(Stack s, StackItem *node, int n) {
	if (n == 0) return 1;
	return copy_recursively(s, node->next, n-1) && stack_push(s, node->value);
}

int process_copy(Stack s) {
	double a;
	
	a = stack_pop(s);

	if (a < 0) {
		return throw_error("Impossivel realizar operação. Motivo: o número de elementos a ser copiados é negativo.\n", PROCESSOR_ERROR_COPY);

	} else if (stack_size(s) < a) {
		return throw_error("Impossivel realizar operação. Motivo: há menos elementos na pilha do que o necessário (stack underflow).\n", PROCESSOR_ERROR_COPY);

	}

	if (copy_recursively(s, s->next, (int)a))
		return PROCESSOR_SUCCESS;
	else
		return throw_error("Impossivel realizar operação. Motivo: não foi possivel inserir novos elementos na memória (erro de alocamento de memória).\n", PROCESSOR_ERROR_COPY);
}

int process_translate_general(Stack s, int n, PROCESSOR_RESULT result) {
	double x0, y0;
	StackItem *cur;
	if (stack_size(s) < 2 * (n + 1)) {
		return throw_error("Impossivel realizar operação. Motivo: há menos elementos na pilha do que o necessário (stack underflow).\n", result);
	}

	y0 = stack_pop(s);
	x0 = stack_pop(s);
	
	cur = s->next;
	for (int i = 0; i < n; i++) {
		cur->value += y0;
		cur->next->value += x0;

		cur = cur->next->next;
	}

	return PROCESSOR_SUCCESS;
}

int process_translate(Stack s) {
	return process_translate_general(s, 1, PROCESSOR_ERROR_TRANSLATE);
}

int process_mtranslate(Stack s) {
	double n;
	if (stack_size(s) < 1) {
		return throw_error("Impossivel realizar operação. Motivo: há menos elementos na pilha do que o necessário (stack underflow).\n", PROCESSOR_ERROR_MTRANSLATE);
	}

	n = stack_pop(s);

	return process_translate_general(s, (int)n, PROCESSOR_ERROR_MTRANSLATE);
}

int process_rotate_general(Stack s, int n, PROCESSOR_RESULT result) {
	double theta, x, y;
	StackItem *cur;
	if (stack_size(s) < 2 * (n + 1)) {
		return throw_error("Impossivel realizar operação. Motivo: há menos elementos na pilha do que o necessário (stack underflow).\n", result);
	}

	theta = stack_pop(s);
	
	cur = s->next;
	for (int i = 0; i < n; i++) {
		y = cur->value;
		x = cur->next->value;

		cur->value = (x * sin(theta) + y * cos(theta)); // calculate new y
		cur->next->value = (x * cos(theta) - y * sin(theta)); // calculate new x

		cur = cur->next->next;
	}

	return PROCESSOR_SUCCESS;
}

int process_rotate(Stack s) {
	return process_rotate_general(s, 1, PROCESSOR_ERROR_ROTATE);
}

int process_mrotate(Stack s) {
	double n;
	if (stack_size(s) < 1) {
		return throw_error("Impossivel realizar operação. Motivo: há menos elementos na pilha do que o necessário (stack underflow).\n", PROCESSOR_ERROR_MROTATE);
	}

	n = stack_pop(s);

	return process_rotate_general(s, (int)n, PROCESSOR_ERROR_MROTATE);
}

int process_line(Drawing d) {
	double x1, x2, y1, y2, t;
	if (stack_size(d->stack) < 5) {
		return throw_error("Impossivel realizar operação. Motivo: há menos elementos na pilha do que o necessário (stack underflow).\n", PROCESSOR_ERROR_LINE);

	}
	
	// printf("[DEBUG] Showing stack before creating line.\n");
	// process_show(d->stack);

	t = stack_pop(d->stack);
	y2 = stack_pop(d->stack);
	x2 = stack_pop(d->stack);
	y1 = stack_pop(d->stack);
	x1 = stack_pop(d->stack);

	if (t < 0) {
		return throw_error("Impossivel realizar operação. Motivo: ao criar um segmento de reta, a grossura não pode ser negativa.\n", PROCESSOR_ERROR_LINE);
	}

	return add_line_segment(d, x1, y1, x2, y2, t) ? PROCESSOR_SUCCESS : PROCESSOR_ERROR_LINE;
}

int process_circle_general(Drawing d, int fill, PROCESSOR_RESULT result) {
	double x, y, r, t;
	if (stack_size(d->stack) < 4) {
		return throw_error("Impossivel realizar operação. Motivo: há menos elementos na pilha do que o necessário (stack underflow).\n", result);

	}

	// printf("[DEBUG] Showing stack before creating circle.\n");
	// process_show(d->stack);
	
	t = stack_pop(d->stack);
	r = stack_pop(d->stack);
	y = stack_pop(d->stack);
	x = stack_pop(d->stack);

	if (t < 0 || r < 0) {
		return throw_error("Impossivel realizar operação. Motivo: ao criar um circulo, a grossura e o raio não podem ser negativos.\n", result);
	}

	return add_circle(d, x, y, r, t, fill) ? PROCESSOR_SUCCESS : result;
}

int process_circle(Drawing d) {
	return process_circle_general(d, 0, PROCESSOR_ERROR_CIRCLE);
}

int process_fillcircle(Drawing d) {
	return process_circle_general(d, 1, PROCESSOR_ERROR_FILL_CIRCLE);
}

void show_recursively(StackItem *node) {
	if (node == NULL) return;
	printf("  %lf\n", node->value);
	show_recursively(node->next);
}

int process_show(Stack s) {
	printf("stack contents (top first):\n");
	show_recursively(s->next);

	printf("\n");

	return PROCESSOR_SUCCESS;
}

int process_tan(Stack s) {
	double a;
	if (stack_size(s) < 1) {
		return throw_error("Impossivel realizar operação. Motivo: há menos elementos na pilha do que o necessário (stack underflow).\n", PROCESSOR_ERROR_TAN);
	}

	a = stack_pop(s);
	
	if (!stack_push(s, tan(a))) {
		return throw_error("Impossivel realizar operação. Motivo: não foi possivel inserir novos elementos na memória (erro de alocamento de memória).\n", PROCESSOR_ERROR_TAN);
	}

	return PROCESSOR_SUCCESS;
}

int process_arcsin(Stack s) {
	double a;
	if (stack_size(s) < 1) {
		return throw_error("Impossivel realizar operação. Motivo: há menos elementos na pilha do que o necessário (stack underflow).\n", PROCESSOR_ERROR_ARCSIN);
	}

	a = stack_pop(s);
	
	if (!stack_push(s, asin(a))) {
		return throw_error("Impossivel realizar operação. Motivo: não foi possivel inserir novos elementos na memória (erro de alocamento de memória).\n", PROCESSOR_ERROR_ARCSIN);
	}

	return PROCESSOR_SUCCESS;
}

int process_arccos(Stack s) {
	double a;
	if (stack_size(s) < 1) {
		return throw_error("Impossivel realizar operação. Motivo: há menos elementos na pilha do que o necessário (stack underflow).\n", PROCESSOR_ERROR_ARCCOS);
	}

	a = stack_pop(s);
	
	if (!stack_push(s, acos(a))) {
		return throw_error("Impossivel realizar operação. Motivo: não foi possivel inserir novos elementos na memória (erro de alocamento de memória).\n", PROCESSOR_ERROR_ARCCOS);
	}

	return PROCESSOR_SUCCESS;
}

int process_arctan(Stack s) {
	double a;
	if (stack_size(s) < 1) {
		return throw_error("Impossivel realizar operação. Motivo: há menos elementos na pilha do que o necessário (stack underflow).\n", PROCESSOR_ERROR_ARCTAN);
	}

	a = stack_pop(s);
	
	if (!stack_push(s, atan(a))) {
		return throw_error("Impossivel realizar operação. Motivo: não foi possivel inserir novos elementos na memória (erro de alocamento de memória).\n", PROCESSOR_ERROR_ARCTAN);
	}

	return PROCESSOR_SUCCESS;
}

int process_eraseline(Drawing d) {
	double x1, x2, y1, y2, t;
	if (stack_size(d->stack) < 5) {
		return throw_error("Impossivel realizar operação. Motivo: há menos elementos na pilha do que o necessário (stack underflow).\n", PROCESSOR_ERROR_ERASELINE);

	}
	
	// printf("[DEBUG] Showing stack before creating line.\n");
	// process_show(d->stack);

	t = stack_pop(d->stack);
	y2 = stack_pop(d->stack);
	x2 = stack_pop(d->stack);
	y1 = stack_pop(d->stack);
	x1 = stack_pop(d->stack);

	if (t < 0) {
		return throw_error("Impossivel realizar operação. Motivo: ao criar uma borracha com segmento de reta, a grossura não pode ser negativa.\n", PROCESSOR_ERROR_ERASELINE);
	}

	return add_line_segment(d, x1, y1, x2, y2, -t) ? PROCESSOR_SUCCESS : PROCESSOR_ERROR_ERASELINE;
}

int process_e(Stack s) {
	if (!stack_push(s, CONST_E)) {
		return throw_error("Impossivel realizar operação. Motivo: não foi possivel inserir novos elementos na memória (erro de alocamento de memória).\n", PROCESSOR_ERROR_E);
	}

	return PROCESSOR_SUCCESS;
}

int process_lg(Stack s) {
	double a;
	if (stack_size(s) < 1) {
		return throw_error("Impossivel realizar operação. Motivo: há menos elementos na pilha do que o necessário (stack underflow).\n", PROCESSOR_ERROR_LG);
	}

	a = stack_pop(s);
	
	if (a < 0) {
		return throw_error("Impossivel realizar operação. Motivo: números negativos não pertencem ao dominio da função logaritmo.\n", PROCESSOR_ERROR_LG);
	
	} else if (!stack_push(s, log2(a))) {
		return throw_error("Impossivel realizar operação. Motivo: não foi possivel inserir novos elementos na memória (erro de alocamento de memória).\n", PROCESSOR_ERROR_LG);
	
	}

	return PROCESSOR_SUCCESS;
}

int process_ln(Stack s) {
	double a;
	if (stack_size(s) < 1) {
		return throw_error("Impossivel realizar operação. Motivo: há menos elementos na pilha do que o necessário (stack underflow).\n", PROCESSOR_ERROR_LN);
	}

	a = stack_pop(s);
	
	if (a < 0) {
		return throw_error("Impossivel realizar operação. Motivo: números negativos não pertencem ao dominio da função logaritmo.\n", PROCESSOR_ERROR_LN);
	
	} else if (!stack_push(s, log(a))) {
		return throw_error("Impossivel realizar operação. Motivo: não foi possivel inserir novos elementos na memória (erro de alocamento de memória).\n", PROCESSOR_ERROR_LN);
	
	}

	return PROCESSOR_SUCCESS;
}

int process_log(Stack s) {
	double a, b;
	if (stack_size(s) < 2) {
		return throw_error("Impossivel realizar operação. Motivo: há menos elementos na pilha do que o necessário (stack underflow).\n", PROCESSOR_ERROR_LOG);
	}

	a = stack_pop(s);
	b = stack_pop(s);
	
	if (b < 0) {
		return throw_error("Impossivel realizar operação. Motivo: números negativos não pertencem ao dominio da função logaritmo.\n", PROCESSOR_ERROR_LOG);
	
	} else if (!stack_push(s, log(b) / log(a))) {
		return throw_error("Impossivel realizar operação. Motivo: não foi possivel inserir novos elementos na memória (erro de alocamento de memória).\n", PROCESSOR_ERROR_LOG);
	
	}

	return PROCESSOR_SUCCESS;
}

int process_abs(Stack s) {
	double a;
	if (stack_size(s) < 1) {
		return throw_error("Impossivel realizar operação. Motivo: há menos elementos na pilha do que o necessário (stack underflow).\n", PROCESSOR_ERROR_ABS);
	}

	a = stack_pop(s);

	if (a < 0) a = -a;
	
	if (!stack_push(s, a)) {
		return throw_error("Impossivel realizar operação. Motivo: não foi possivel inserir novos elementos na memória (erro de alocamento de memória).\n", PROCESSOR_ERROR_ABS);
	}

	return PROCESSOR_SUCCESS;
}

