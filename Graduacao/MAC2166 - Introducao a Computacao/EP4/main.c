/***************************************************************/
/**                                                           **/
/**   Lucas Moreira Santos                          9345064   **/
/**   Exercício-Programa 04                                   **/
/**   Professor:  Fernando Mário de Oliveira Filho            **/
/**   Turma: 05                                               **/
/**                                                           **/
/***************************************************************/

#include <stdio.h>
#include <string.h>
#define MAXLINHA 400
#define MAXCOLUNA 400
#define JANELA_MAX 50
#define MAX_NAME 256	/* Número máximo de caracteres, incluindo o ".pgm" */


/*
	Protótipos
*/

void negativo(int m[MAXLINHA][MAXCOLUNA], int linhas, int colunas);
void rebatimentoVertical(int m[MAXLINHA][MAXCOLUNA], int linhas, int colunas);
void rebatimentoHorizontal(int m[MAXLINHA][MAXCOLUNA], int linhas, int colunas);
void rotacao(int m[MAXLINHA][MAXCOLUNA], int *linhas, int *colunas);
void corte(int m[MAXLINHA][MAXCOLUNA], int *linhas, int *colunas, int xsup, int ysup, int xinf, int yinf);
void filtroMediana(int m[MAXLINHA][MAXCOLUNA], int linhas, int colunas, int larguraJanela);
void filtroMedia(int m[MAXLINHA][MAXCOLUNA], int linhas, int colunas, int larguraJanela);
void filtroErosao(int m[MAXLINHA][MAXCOLUNA], int linhas,int colunas, int larguraJanela);
void filtroDilatacao(int m[MAXLINHA][MAXCOLUNA], int linhas, int colunas, int larguraJanela);
void limiarizacao(int m[MAXLINHA][MAXCOLUNA], int linhas, int colunas, int k);
void filtroBorda1(int m[MAXLINHA][MAXCOLUNA], int linhas, int colunas, int larguraJanela, int k);
void filtroBorda2(int m[MAXLINHA][MAXCOLUNA], int linhas, int colunas, int larguraJanela, int k);
void filtroBorda3(int m[MAXLINHA][MAXCOLUNA], int linhas, int colunas, int larguraJanela, int k);

int grava_pgm(char *prefixo_do_nome, int m[MAXLINHA][MAXCOLUNA], int linhas, int colunas, int maiorValor);
int le_pgm(char *prefixo_do_nome, int m[MAXLINHA][MAXCOLUNA], int *linhas, int *colunas, int *maiorValor);

void imprime_menu();
void imprime_matriz(int m[MAXLINHA][MAXCOLUNA], int linhas, int colunas);
void swap(int *a, int *b);
int min(int a, int b);
int max(int a, int b);
void copia_matriz(int de[MAXLINHA][MAXCOLUNA], int para[MAXLINHA][MAXCOLUNA], int linhas, int colunas);
void subtracao_matriz(int m[MAXLINHA][MAXCOLUNA], int a[MAXLINHA][MAXCOLUNA], int linhas, int colunas);
void merge(int v[], int esquerda, int meio, int direita);
void mergesort(int v[], int esquerda, int direita);


/*
	Função main
*/

int main() {
	int m[MAXLINHA][MAXCOLUNA], linhas, colunas, maiorValor;
	int c_m[MAXLINHA][MAXCOLUNA], c_linhas, c_colunas, c_maiorValor;
	char nome_arquivo[MAX_NAME], c_nome_arquivo[MAX_NAME], complemento[MAX_NAME], menu = '9';
	int a, b, c, d, t = 0, index_char;

	printf("Digite o nome do arquivo de entrada: ");
	scanf("%s", nome_arquivo);

	while (le_pgm(nome_arquivo, m, &linhas, &colunas, &maiorValor) == 0) {
		printf("Digite o nome do arquivo de entrada: ");
		scanf("%s", nome_arquivo);
	}

	printf("Arquivo %s.pgm carregado com sucesso.\n", nome_arquivo);
	imprime_menu();


	while(menu != 's') {
		if (menu == 'c') {
			printf("Digite o nome do arquivo de entrada: ");
			scanf("%s", nome_arquivo);

			if (le_pgm(nome_arquivo, m, &linhas, &colunas, &maiorValor) == 1) {
				t = 0;

				printf("Arquivo %s.pgm carregado com sucesso.\n\n", nome_arquivo);

			} else return 0;


		} else if (menu == 'a') {
			imprime_menu();
		

		} else if (menu == 't') {
			imprime_matriz(m, linhas, colunas);


		} else if (menu == 'n') {
			negativo(m, linhas, colunas);
			complemento[t++] = 'n';
			printf("Operacao realizada com sucesso.\n");

		} else if (menu == 'r') {
			rotacao(m, &linhas, &colunas);
			complemento[t++] = 'r';
			printf("Operacao realizada com sucesso.\n");

		} else if (menu == 'v') {
			rebatimentoVertical(m, linhas, colunas);
			complemento[t++] = 'v';
			printf("Operacao realizada com sucesso.\n");


		} else if (menu == 'h') {
			rebatimentoHorizontal(m, linhas, colunas);
			complemento[t++] = 'h';
			printf("Operacao realizada com sucesso.\n");


		} else if (menu == 'x') {
			printf("Informe x superior: ");
			scanf("%d", &a);

			printf("Informe y superior: ");
			scanf("%d", &b);

			printf("Informe x inferior: ");
			scanf("%d", &c);

			printf("Informe y inferior: ");
			scanf("%d", &d);

			if (a < 0 || b < 0 || c > (linhas - 1) || d > (colunas - 1) || a > c || b > d) {
				printf("Limites invalidos\n\n");

			} else {
				corte(m, &linhas, &colunas, a, b, c, d);
				complemento[t++] = 'x';
				printf("Operacao realizada com sucesso.\n");

			}



		} else if (menu == 'e') {
			printf("Digite o tamanho da janela: ");
			scanf("%d", &a);

			while(a < 3 || a > 50) {
				printf("Tamanho invalido. A janela deve ser entre 3 e 50.\n");
				printf("Digite o tamanho da janela: ");
				scanf("%d", &a);
			}

			filtroErosao(m, linhas, colunas, a);
			complemento[t++] = 'e';
			printf("Operacao realizada com sucesso.\n");


		} else if (menu == 'd') {
			printf("Digite o tamanho da janela: ");
			scanf("%d", &a);

			while(a < 3 || a > 50) {
				printf("Tamanho invalido. A janela deve ser entre 3 e 50.\n");
				printf("Digite o tamanho da janela: ");
				scanf("%d", &a);
			}

			filtroDilatacao(m, linhas, colunas, a);
			complemento[t++] = 'd';
			printf("Operacao realizada com sucesso.\n");


		} else if (menu == 'm') {
			printf("Digite o tamanho da janela: ");
			scanf("%d", &a);

			while(a < 3 || a > 50) {
				printf("Tamanho invalido. A janela deve ser entre 3 e 50.\n");
				printf("Digite o tamanho da janela: ");
				scanf("%d", &a);
			}

			filtroMediana(m, linhas, colunas, a);
			complemento[t++] = 'm';
			printf("Operacao realizada com sucesso.\n");


		} else if (menu == 'z') {
			printf("Digite o tamanho da janela: ");
			scanf("%d", &a);

			while(a < 3 || a > 50) {
				printf("Tamanho invalido. A janela deve ser entre 3 e 50.\n");
				printf("Digite o tamanho da janela: ");
				scanf("%d", &a);
			}

			filtroMedia(m, linhas, colunas, a);
			complemento[t++] = 'z';
			printf("Operacao realizada com sucesso.\n");


		} else if (menu == '1') {
			printf("Digite o tamanho da janela: ");
			scanf("%d", &a);

			while(a < 3 || a > 50) {
				printf("Tamanho invalido. A janela deve ser entre 3 e 50.\n");
				printf("Digite o tamanho da janela: ");
				scanf("%d", &a);
			}

			printf("Informe o valor de k: ");
			scanf("%d", &b);

			filtroBorda1(m, linhas, colunas, a, b);
			complemento[t++] = '1';
			printf("Operacao realizada com sucesso.\n");


		} else if (menu == '2') {
			printf("Digite o tamanho da janela: ");
			scanf("%d", &a);

			while(a < 3 || a > 50) {
				printf("Tamanho invalido. A janela deve ser entre 3 e 50.\n");
				printf("Digite o tamanho da janela: ");
				scanf("%d", &a);
			}

			printf("Informe o valor de k: ");
			scanf("%d", &b);

			filtroBorda2(m, linhas, colunas, a, b);
			complemento[t++] = '2';
			printf("Operacao realizada com sucesso.\n");


		} else if (menu == '3') {
			printf("Digite o tamanho da janela: ");
			scanf("%d", &a);

			while(a < 3 || a > 50) {
				printf("Tamanho invalido. A janela deve ser entre 3 e 50.\n");
				printf("Digite o tamanho da janela: ");
				scanf("%d", &a);
			}

			printf("Informe o valor de k: ");
			scanf("%d", &b);

			filtroBorda3(m, linhas, colunas, a, b);
			complemento[t++] = '3';
			printf("Operacao realizada com sucesso.\n");


		} else if (menu == 'g') {
			for(index_char = 0; nome_arquivo[index_char] != 0; index_char++) {
				c_nome_arquivo[index_char] = nome_arquivo[index_char];
			}

			if (t > 0)
				c_nome_arquivo[index_char++] = '-';

			for(a = 0; a < t; a++)
				c_nome_arquivo[index_char++] = complemento[a];

			while(c_nome_arquivo[index_char] != 0)
				c_nome_arquivo[index_char++] = 0;

			grava_pgm(c_nome_arquivo, m, linhas, colunas, maiorValor);
			printf("%s.pgm\nArquivo %s.pgm gravado com sucesso.\n", c_nome_arquivo, c_nome_arquivo);


		} else if (menu == 'C') {
			printf("Digite o nome do arquivo para comparacao: \n");
			scanf("%s", c_nome_arquivo);

			if (le_pgm(c_nome_arquivo, c_m, &c_linhas, &c_colunas, &c_maiorValor) == 1) {
				if (c_linhas != linhas || c_colunas != colunas) {
					printf("As matrizes tem dimensoes diferentes.\n");

				} else {
					/* Compara valor a valor e verifica se é igual ou diferente */
					c = 1;
					for(a = 0; a < linhas; a++) {
						for(b = 0; b < colunas; b++) {
							if (m[a][b] != c_m[a][b]) {
								c = 0;
								break;
							}
						}

						if (c == 0) break;
					}

					if (c == 0) printf("As matrizes tem dimensoes diferentes.\n");
					else printf("As matrizes sao iguais.\n");
				}

			} else {
				printf("Falha ao carregar arquivo %s.pgm de comparacao.\n", c_nome_arquivo);

			}

			
		} else if (menu != '9') {
			printf("Comando invalido\n");

		}

		printf("Digite um comando: ");
		scanf(" %c", &menu);
	}

	

	return 0;
}


/*
	Demais funções
*/

/* ----------------------------------------------
  Le um arquivo no formato PGM.
   prefixo_do_nome  : prefixo do arquivo pgm
   m                : matriz correspondente a imagem lida
   linhas           : numero de linhas da matriz
   colunas          : numero de colunas da matriz
   max_value        : maior valor na matriz
  ---------------------------------------------- */
int le_pgm(char* prefixo_do_nome, int m[MAXLINHA][MAXCOLUNA], int *linhas, int *colunas, int *maiorValor){
	FILE *arq;
	char key[128];
	int i, j, aux;
	char fname[MAX_NAME];
	
	/* Monta o nome do arquivo */
	strcpy(fname, prefixo_do_nome);
	strcat(fname, ".pgm");
	
	/* Abre o o arquivo de entrada para leitura */
	arq = fopen(fname, "r");
	if (arq == NULL) {
		printf("Erro na abertura do arquivo %s\n",fname);
		return 0;
	}

	/* Le dados do cabecalho */
	aux = fscanf(arq, "%s", key);
	if (aux != 1) {
		printf("Erro na letura do arquivo %s\n", fname);
		return 0;
	}

	if(strcmp(key,"P2") != 0) {
		printf("Formato desconhecido\n") ;
		fclose(arq) ;
		return 0;
	}
   
	aux = fscanf(arq, "%d %d %d", colunas, linhas, maiorValor) ;
	if (aux != 3) {
		printf("Formato incorreto\n") ;
		fclose(arq) ;
		return 0;
	}
   
   	/* Le a matriz (imagem) que se segue  */
	for(i = 0; i < *linhas; i++) {
		for(j = 0; j < *colunas; j++) {
			fscanf(arq, "%d", &m[i][j]);
		}
	}
	
	/* Fecha arquivo */
	fclose(arq);
	
	return 1;
}

/* ----------------------------------------------
  Escreve um arquivo, no formato PGM.
   prefixo_do_nome  : prefixo do arquivo pgm
   m                : matriz correspondente a imagem lida
   linhas           : numero de linhas da matriz
   colunas          : numero de colunas da matriz
   max_value        : maior valor na matriz
 ---------------------------------------------- */
int grava_pgm(char* prefixo_do_nome, int m[MAXLINHA][MAXCOLUNA], int linhas, int colunas, int maiorValor) {
	FILE *arq;
	int i, j;
	char fname[MAX_NAME];
	
	/* Monta o nome do arquivo */
	strcpy(fname, prefixo_do_nome);
	strcat(fname,".pgm");
	
	/* Abre o o arquivo para gravacao */
	arq = fopen(fname, "w");
	if (arq == NULL){
		printf("Erro na abertura do arquivo %s\n",fname);
		return 0;
	}
   
	/* Grava dados do cabecalho */
	fprintf(arq, "P2\n");
	fprintf(arq, "%d %d\n%d\n", colunas, linhas, maiorValor);
   
	/* Grava a matriz (imagem) que se segue  */
	for (i = 0; i < linhas; i++) {
		for (j = 0; j < colunas; j++) {
			fprintf(arq, "%d ", m[i][j]);
		}
		fprintf(arq, "\n");
	}
	
	/* Fecha arquivo */
	fclose(arq);
	
	return 1;
}

/* Imprime o menu */
void imprime_menu() {
	printf("c - carga\nt - exibicao na tela\nn - negativo\nr - rotacao\nv - espelhamento vertical\nh - espelhamento horizontal\nx - corte\ne - filtro da erosao\nd - filtro da dilatacao\nm - filtro da mediana\nz - filtro da media\n1 - filtro de bordas 1\n2 - filtro de bordas 2\n3 - filtro de bordas 3\ng - gravacao\nC - comparacao\na - ajuda\ns - sair\n\n");
}

/* Imprime uma matriz */
void imprime_matriz(int m[MAXLINHA][MAXCOLUNA], int linhas, int colunas) {
	int i, j;
	for (i = 0; i < linhas; i++) {
		for (j = 0; j < colunas; j++) {
			printf("%3d ", m[i][j]);
		}

		printf("\n");
	}

	printf("\n");
}

/* Troca os valores de A com B */
void swap(int *a, int *b) {
	int c = *a;
	*a = *b;
	*b = c;
}

/* Dado dois inteiros, retorna o menor */
int min(int a, int b) {
	if (a < b) return a;
	else return b;
}

/* Dado dois inteiros, retorna o maior */
int max(int a, int b) {
	if (a > b) return a;
	else return b;
}

/* Replica a matriz "de" em "para" */
void copia_matriz(int de[MAXLINHA][MAXCOLUNA], int para[MAXLINHA][MAXCOLUNA], int linhas, int colunas) {
	int i, j;
	for (i = 0; i < linhas; i++)
		for (j = 0; j < colunas; j++)
			para[i][j] = de[i][j];
}

/* Realiza a subtração de M - A. Para cada elemento de i e j pertencente ao dominio da matriz, temos: m(i,j) -= a(i,j) */
void subtracao_matriz(int m[MAXLINHA][MAXCOLUNA], int a[MAXLINHA][MAXCOLUNA], int linhas, int colunas) {
	int i, j;
	for (i = 0; i < linhas; i++)
		for (j = 0; j < colunas; j++)
			m[i][j] -= a[i][j];
}

/*
	Dado um array A e dois intervalos continuos [esquerda, meio] e [meio, direita], temos A ordenado em ambos intervalos. 
	Retorna o array A ordenado por completo no intervalo [esquerda, direita]
	Algoritmo de Robert Sedgewick, Algorithms in C, 3rd. ed., vol. 1, Addison Wesley Longman, 1998.
	http://www.ime.usp.br/~pf/algoritmos/aulas/mrgsrt.html
*/
void merge(int v[], int esquerda, int meio, int direita) {
	int aux[MAXLINHA * MAXCOLUNA];
	int i, j, k;

	for (i = 0, k = esquerda; k < meio; k++, i++) aux[i] = v[k];
	for (i = (direita - esquerda - 1), k = meio; k < direita; k++, i--) aux[i] = v[k];

	i = 0;
	j = direita - esquerda - 1;

	for(k = esquerda; k < direita; k++) {
		if (aux[i] <= aux[j]) v[k] = aux[i++];
		else v[k] = aux[j--];
	}
}

/*
	Baseado no conceito dividir para conquistar, dividimos o array em duas partes e ordenamos cada uma delas
	enquanto a sentença (esquerda < direita) for verdadeira
	Retorna um array V ordenado não-decrescente
*/
void mergesort(int v[], int esquerda, int direita) {
	int meio;
	if (esquerda < direita - 1) {
		meio = (esquerda + direita) / 2;
		mergesort(v, esquerda, meio);
		mergesort(v, meio, direita);
		merge(v, esquerda, meio, direita);
	}
}

void negativo(int m[MAXLINHA][MAXCOLUNA], int linhas, int colunas) {
	int i, j;
	for (i = 0; i < linhas; i++)
		for (j = 0; j < colunas; j++)
			m[i][j] = 255 - m[i][j];
}

void rebatimentoVertical(int m[MAXLINHA][MAXCOLUNA], int linhas, int colunas) {
	int i, j;
	for (i = 0; i < linhas; i++)
		for (j = 0; j < (colunas / 2); j++)
			swap(&m[i][colunas - 1 - j], &m[i][j]);
}

void rebatimentoHorizontal(int m[MAXLINHA][MAXCOLUNA], int linhas, int colunas) {
	int i, j;
	for (i = 0; i < (linhas / 2); i++)
		for (j = 0; j < colunas; j++)
			swap(&m[linhas - 1 - i][j], &m[i][j]);
}

void rotacao(int m[MAXLINHA][MAXCOLUNA], int *linhas, int *colunas) {
	/* Calcula a transposta da matriz e rebate verticalmente a matriz */
	int max, i, j;

	if ((*linhas) > (*colunas)) max = *linhas;
	else max = *colunas;

	for (i = 0; i < max - 1; i++)
		for (j = i + 1; j < max; j++)
			swap(&m[i][j], &m[j][i]);

	swap(linhas, colunas);
	rebatimentoVertical(m, *linhas, *colunas);
}

void corte(int m[MAXLINHA][MAXCOLUNA], int *linhas, int *colunas, int xsup, int ysup, int xinf, int yinf) {
	int i, j;

	for (i = xsup; i <= xinf; i++)
		for (j = ysup; j <= yinf; j++)
			m[i - xsup][j - ysup] = m[i][j];

	*linhas = xinf - xsup + 1;
	*colunas = yinf - ysup + 1;
}

void filtroMediana(int m[MAXLINHA][MAXCOLUNA], int linhas, int colunas, int larguraJanela) {
	int v_array[256];
	int m_copy[MAXLINHA][MAXCOLUNA];
	int i, j, a, b, pos;
	int xsup, ysup, xinf, yinf;
	int offset = (larguraJanela - 1) / 2;

	copia_matriz(m, m_copy, linhas, colunas);

	for (i = 0; i < 256; i++)
		v_array[i] = 0;

	for (i = 0; i < linhas; i++) {
		for (j = 0; j < colunas; j++) {
			xsup = max(0, j - offset);
			ysup = max(0, i - offset);
			xinf = min(colunas - 1, j + offset);
			yinf = min(linhas - 1, i + offset);
			pos = 0;

			/* Procuro a mediana no meu vetor ordenado. */
			for(a = ysup; a <= yinf; a++) {
				for(b = xsup; b <= xinf; b++) {
					v_array[pos++] = m_copy[a][b];
				}
			}

			mergesort(v_array, 0, pos);

			m[i][j] = v_array[pos/2];
		}
	}
}

void filtroMedia(int m[MAXLINHA][MAXCOLUNA], int linhas, int colunas, int larguraJanela) {
	int m_copy[MAXLINHA][MAXCOLUNA];
	int i, j, a, b, sum;
	int xsup, ysup, xinf, yinf;
	int offset = (larguraJanela - 1) / 2;

	copia_matriz(m, m_copy, linhas, colunas);

	for (i = 0; i < linhas; i++) {
		for (j = 0; j < colunas; j++) {
			xsup = max(0, j - offset);
			ysup = max(0, i - offset);
			xinf = min(colunas - 1, j + offset);
			yinf = min(linhas - 1, i + offset);
			sum = 0;

			for(a = ysup; a <= yinf; a++)
				for(b = xsup; b <= xinf; b++)
					sum += m_copy[a][b];

			m[i][j] = sum / ((xinf - xsup + 1) * (yinf - ysup + 1));
		}
	}
}

void filtroErosao(int m[MAXLINHA][MAXCOLUNA], int linhas,int colunas, int larguraJanela) {
	int m_copy[MAXLINHA][MAXCOLUNA];
	int i, j, a, b, min_value;
	int xsup, ysup, xinf, yinf;
	int offset = (larguraJanela - 1) / 2;

	copia_matriz(m, m_copy, linhas, colunas);

	for (i = 0; i < linhas; i++) {
		for (j = 0; j < colunas; j++) {
			xsup = max(0, j - offset);
			ysup = max(0, i - offset);
			xinf = min(colunas - 1, j + offset);
			yinf = min(linhas - 1, i + offset);
			min_value = 256;

			for(a = ysup; a <= yinf; a++)
				for(b = xsup; b <= xinf; b++)
					min_value = min(min_value, m_copy[a][b]);

			m[i][j] = min_value;
		}
	}
}

void filtroDilatacao(int m[MAXLINHA][MAXCOLUNA], int linhas, int colunas, int larguraJanela) {
	int m_copy[MAXLINHA][MAXCOLUNA];
	int i, j, a, b, max_value;
	int xsup, ysup, xinf, yinf;
	int offset = (larguraJanela - 1) / 2;

	copia_matriz(m, m_copy, linhas, colunas);

	for (i = 0; i < linhas; i++) {
		for (j = 0; j < colunas; j++) {
			xsup = max(0, j - offset);
			ysup = max(0, i - offset);
			xinf = min(colunas - 1, j + offset);
			yinf = min(linhas - 1, i + offset);
			max_value = -1;

			for(a = ysup; a <= yinf; a++)
				for(b = xsup; b <= xinf; b++)
					max_value = max(max_value, m_copy[a][b]);

			m[i][j] = max_value;
		}
	}
}

void limiarizacao(int m[MAXLINHA][MAXCOLUNA], int linhas, int colunas, int k) {
	int i, j;
	for (i = 0; i < linhas; i++)
		for (j = 0; j < colunas; j++)
			if (m[i][j] >= k) m[i][j] = 255;
			else m[i][j] = 0;
}

void filtroBorda1(int m[MAXLINHA][MAXCOLUNA], int linhas, int colunas, int larguraJanela, int k) {
	int aux[MAXLINHA][MAXCOLUNA];

	copia_matriz(m, aux, linhas, colunas);
	filtroDilatacao(m, linhas, colunas, larguraJanela);
	filtroErosao(aux, linhas, colunas, larguraJanela);
	subtracao_matriz(m, aux, linhas, colunas);
	limiarizacao(m, linhas, colunas, k);
}

void filtroBorda2(int m[MAXLINHA][MAXCOLUNA], int linhas, int colunas, int larguraJanela, int k) {
	int aux[MAXLINHA][MAXCOLUNA];

	copia_matriz(m, aux, linhas, colunas);
	filtroErosao(aux, linhas, colunas, larguraJanela);
	subtracao_matriz(m, aux, linhas, colunas);
	limiarizacao(m, linhas, colunas, k);
}

void filtroBorda3(int m[MAXLINHA][MAXCOLUNA], int linhas, int colunas, int larguraJanela, int k) {
	int aux[MAXLINHA][MAXCOLUNA];

	copia_matriz(m, aux, linhas, colunas);
	filtroDilatacao(m, linhas, colunas, larguraJanela);
	subtracao_matriz(m, aux, linhas, colunas);
	limiarizacao(m, linhas, colunas, k);
}
