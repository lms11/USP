#include <stdio.h>
#include <stdlib.h>

FILE *outfile;

void swap(int *a, int *b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void printa(int *v , int n) {
	fprintf(outfile, "{");
	fprintf(outfile, "%d", v[0]);
	for (int x = 1; x < n; x++) fprintf(outfile, ",%d", v[x]);
	fprintf(outfile, "},");
}

void processEachPermutation(int n, int *v, int *p) {
   int i, j, tmp; 
   printa(v, n);
   i = 1;   
   while(i < n) {
      if (p[i] < i) {
         j = i % 2 * p[i];   
         swap(&v[j], &v[i]);
         printa(v, n);
         p[i]++;             
         i = 1;              
      } else {               
         p[i] = 0;           
         i++;                
      } 
   } 
}

long long int fatorial(int n) {
	long long int res = 1;
	while(n > 0) res *= n--;
	return res;
}

int main() {
	int num_elements = 8;

	outfile = fopen("saida.c", "w");

	

	for (num_elements = 8; num_elements <= 9; num_elements++) {
		int *elements = malloc(num_elements * sizeof(int)), *p = malloc((num_elements + 1) * sizeof(int));
		if (!elements) exit(1); // TODO: melhorar retorno de erro
		fprintf(outfile, "int %d_elements[%lld][%d] = {", num_elements, fatorial(num_elements), num_elements);

		for (int x = 0; x < num_elements; x++) {
			elements[x] = (x+1);
			p[x] = 0;
		}

		processEachPermutation(num_elements, elements, p);
		free(elements);
		free(p);

		fprintf(outfile, "};\n");
	}


	return 0;
}