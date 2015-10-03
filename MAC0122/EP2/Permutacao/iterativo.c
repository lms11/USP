#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void processEachPermutation(int n, int *v, int *p) {
   int i, j, tmp; 

   i = 1;   
   while(i < n) {
      if (p[i] < i) {
         j = i % 2 * p[i];   
         swap(&v[j], &v[i]);
         p[i]++;             
         i = 1;              
      } else {               
         p[i] = 0;           
         i++;                
      } 
   } 
} 

int main() {
	int num_elements = 12;
	int *elements = malloc(num_elements * sizeof(int)), *p = malloc((num_elements + 1) * sizeof(int));
	if (!elements) exit(1); // TODO: melhorar retorno de erro

	for (int x = 0; x < num_elements; x++) {
		elements[x] = (x+1);
		p[x] = 0;
	}

	processEachPermutation(num_elements, elements, p);
	free(elements);
	free(p);

	return 0;
}