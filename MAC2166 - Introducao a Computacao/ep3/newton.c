/***************************************************************/
/**                                                           **/
/**   Lucas Moreira Santos                          9345064   **/
/**   Exercício-Programa 03                                   **/
/**   Professor:  Fernando Mário de Oliveira Filho            **/
/**   Turma: 05                                               **/
/**                                                           **/
/***************************************************************/

#include <stdio.h>

/*
	Prototipos
*/

void calcula(double x_real, double x_imag, double *p_real, double *p_imag, double *d_real, double *d_imag);
void multiplica(double *ret_real, double *ret_imag, double x_real, double x_imag, double y_real, double y_imag);
int newton(double *x_real, double *x_imag, int max_iter, double eps);


/*
	Funcao que calcula o polinomio
*/

#include "polinomio.c"


/*
	Funcao main
*/

int main() {
	double l, u, eps, delta, x_real, x_imag;
	int n, max_iter, r, s, success;
	FILE *out = fopen("saida.txt", "w");

	if (!out) {
      printf("Nao consegui abrir o arquivo para gravacao! (saida.txt)\n");
      return 0;
    }

	printf("Digite o valor de l       : ");
	scanf("%lf", &l);

	printf("Digite o valor de u       : ");
	scanf("%lf", &u);

	printf("Digite o valor de N       : ");
	scanf("%d", &n);

	printf("Digite o valor de max_iter: ");
	scanf("%d", &max_iter);

	printf("Digite o valor de epsilon : ");
	scanf("%lf", &eps);

	delta = (u - l) / n;

	fprintf(out, "%d\n", n);

	for (r = 0; r <= n; r++) {
		for (s = 0; s <= n; s++) {
			x_real = l + r * delta;
			x_imag = l + s * delta;
			success = newton(&x_real, &x_imag, max_iter, eps);

			if (s > 0) fprintf(out, " ");

			if (success == 0) {
				fprintf(out, "N");
			} else {
				fprintf(out, "%.10g %.10g", x_real, x_imag);
			}
		}

		fprintf(out, "\n");
	}

	fclose(out);

	return 0;
}


/*
	Implementacao das funções
*/

/* 
	Coloca em *ret_real e *ret_imag as partes real e imaginária do produto (x_real+x_imag⋅i)(y_real+y_imag⋅i)
	(x_real+x_imag⋅i)(y_real+y_imag⋅i) = (x_real * y_real) + (x_real * y_imag * i) + (y_real * x_imag * i) + (-1 * x_imag * y_imag)
*/
void multiplica(double *ret_real, double *ret_imag, double x_real, double x_imag, double y_real, double y_imag) {
	*ret_real = (x_real * y_real) - (x_imag * y_imag);
	*ret_imag = (x_real * y_imag) + (y_real * x_imag);
}

/*
	Recebe um valor x (parte real e imaginária) e, dado um epsilon e um número máximo de iterações,
	encontra para qual raiz o x dado converge. Se converjir, retorna 1. Caso não convirja para nenhuma, retorna 0.
	Os ponteiros *x_real e *x_imag terá seus valores alterados. Caso convirja, seus valores será a raiz.
*/
int newton(double *x_real, double *x_imag, int max_iter, double eps) {
	double p_real, p_imag, d_real, d_imag, m_real, m_imag;
	
	while (max_iter > 0) {
		calcula(*x_real, *x_imag, &p_real, &p_imag, &d_real, &d_imag);

		/* Verifica se |f(x)| <= epsilon. Se for, achamos a raiz que x_real e x_imag converge. */
		if (p_real <= eps && p_real >= -eps && p_imag <= eps && p_imag >= -eps) return 1;
		
		/* Verifica se |f'(x)| <= epsilon. Se for, significa que x_real e x_imag não converge para nenhuma raiz. */
		if (d_real <= eps && d_real >= -eps && d_imag <= eps && d_imag >= -eps) return 0;


		/*
			Divide f(x) / f'(x). Como f'(x) é um numero complexo, multiplicamos pelo
			conjugado (em cima e embaixo) para removermos o número complexo do denominador
		*/

		multiplica(&m_real, &m_imag, p_real, p_imag, d_real, -d_imag);
		m_real /= ((d_real * d_real) + (d_imag * d_imag));
		m_imag /= ((d_real * d_real) + (d_imag * d_imag));

		*x_real -= m_real;
		*x_imag -= m_imag;

		max_iter--;
	}

	return 0;
}
