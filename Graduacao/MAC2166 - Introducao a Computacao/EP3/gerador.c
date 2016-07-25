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
	Gerador baseado no Método de Horner
*/

int main() {
	int grau;
	double real, imag;
	FILE	*in  = fopen("polinomio.txt", "r"),
			*out = fopen("polinomio.c", "w");

    if (!in) {
      printf("Nao consegui abrir o arquivo para leitura! (polinomio.txt)\n");
      return 0;
    }

    if (!out) {
      printf("Nao consegui abrir o arquivo para gravacao! (polinomio.c)\n");
      return 0;
    }

    fscanf(in, "%d", &grau);
	fscanf(in, "%lf %lf", &real, &imag);

	fprintf(out, "/* Gerado para o polinomio de grau %d usando método de Horner */\n\n", grau);
    fprintf(out, "void calcula(double x_real, double x_imag, double *p_real, double *p_imag, double *d_real, double *d_imag) {\n");
	fprintf(out, "    multiplica(p_real, p_imag, %.10g, %.10g, x_real, x_imag);\n", real, imag);
	fprintf(out, "    multiplica(d_real, d_imag, %.10g, %.10g, %d * x_real, %d * x_imag);\n", real, imag, grau, grau);
	grau--;

    while (grau >= 0) {
    	fscanf(in, "%lf %lf", &real, &imag);
 	
		if (real != 0) fprintf(out, "    *p_real += %.10g;\n", real);
		if (imag != 0) fprintf(out, "    *p_imag += %.10g;\n", imag);

		if (grau > 0) {
			if (real != 0) fprintf(out, "    *d_real += %d * %.10g;\n", grau, real);
			if (imag != 0) fprintf(out, "    *d_imag += %d * %.10g;\n", grau, imag);

			fprintf(out, "    multiplica(p_real, p_imag, *p_real, *p_imag, x_real, x_imag);\n");
			
			if (grau > 1) 
				fprintf(out, "    multiplica(d_real, d_imag, *d_real, *d_imag, x_real, x_imag);\n");
 		
 		}

 		grau--;
    }

    fprintf(out, "\n}\n");

    fclose(in);
    fclose(out);

    return 0;
}	
