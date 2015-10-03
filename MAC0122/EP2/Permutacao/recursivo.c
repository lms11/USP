#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void processEachPermutation(int n, int *v, int index) {
	if (n == index) {
		return;

	} else for (int j = index; j < n; j++) {
		swap(&v[index], &v[j]);
		processEachPermutation(n, v, index + 1);
		swap(&v[index], &v[j]);

	}
}

int main() {
	int num_elements = 11;
	int *elements = malloc(num_elements * sizeof(int));
	if (!elements) exit(1); // TODO: melhorar retorno de erro

	for (int x = 0; x < num_elements; x++) {
		elements[x] = (x+1);
	}

	processEachPermutation(num_elements, elements, 0);
	free(elements);

	return 0;
}