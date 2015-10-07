/***************************************************************/
/**                                                           **/
/**   Luca Tornato Serafini                         9373434   **/
/**   Lucas Moreira Santos                          9345064   **/
/**   Mardem Humberto Santos Junior 				9065976   **/
/**   Exercício-Programa 01                                   **/
/**   Professor:  Fernando Mário de Oliveira Filho            **/
/**   MAC0122 - Princípios de Desenvolvimento de Algoritmos   **/
/**                                                           **/
/***************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

// Variaveis globais
Node **curNode;
int elements[20], p[20], v_copy[20];


// Função auxiliar para trocar valores de dois inteiros
void swap(int *a, int *b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

Node* createNode() {
	Node *newNode = malloc(sizeof(struct node_struct));
	if (!newNode) exit(1); // TODO: arrumar isso aqui pra retornar erros e tal

	newNode->left = newNode->right = NULL;
	newNode->x = newNode->y = newNode->width = 0.0;

	return newNode;
}

void changeCurNode(int a, int b) {
	if (a < b) {
		if (!((*curNode)->left))
			(*curNode)->left = createNode();
		
		*curNode = (*curNode)->left;

	} else {
		if (!((*curNode)->right))
			(*curNode)->right = createNode();
		
		*curNode = (*curNode)->right;
	}
}

int less(int a, int b) {
	changeCurNode(a, b);
	return a < b;
}

int greater(int a, int b) {
	changeCurNode(a, b);
	return a > b;
}

int qsort_compare_func(const void * a, const void * b) {
	/*
		Como estamos trabalhando com um vetor de elementos onde não temos repetição de elementos, 
		é seguro retornar apenas se um elemento é maior ou menor que o outro, ignorando em caso de igualdade.
	*/
	int res = less(*(int *)a, *(int *)b);
	return res ? -1 : 1;
}

Node* process(char algorithm[20], int num_elements) {
	if (num_elements > 20) return NULL;

	Node *head = createNode();

	for (int x = 0; x < num_elements; x++) {
		elements[x] = (x+1);
		p[x] = 0;
	}

	generatePermutations(algorithm, num_elements, elements, p, head);

	return head;
}

void processEachPermutation(int *elements, int num_elements, char *algorithm, Node *head) {
	curNode = &head;

	if (strcmp(algorithm, "heapsort") == 0) {
		for (int x = 0; x < num_elements; x++) {
			v_copy[x+1] = elements[x];
		}

		ep_heapsort(v_copy, num_elements + 1);


	} else {
		for (int x = 0; x < num_elements; x++) {
			v_copy[x] = elements[x];
		}

		if (strcmp(algorithm, "qsort") == 0) {
			qsort(v_copy, num_elements, sizeof(int), qsort_compare_func);

		} else if (strcmp(algorithm, "selection_sort") == 0) {
			selection_sort(v_copy, num_elements);

		} else if (strcmp(algorithm, "insertion_sort") == 0) {
			insertion_sort(v_copy, num_elements);

		} else if (strcmp(algorithm, "bubble_sort") == 0) {
			bubble_sort(v_copy, num_elements);

		} else if (strcmp(algorithm, "quicksort_random") == 0) {
			ep_quicksort(v_copy, 0, num_elements - 1, 1);

		} else if (strcmp(algorithm, "quicksort") == 0) {
			ep_quicksort(v_copy, 0, num_elements - 1, 0);

		} else if (strcmp(algorithm, "mergesort") == 0) {
			ep_mergesort(v_copy, 0, num_elements);

		}

	}
}

void generatePermutations(char *algorithm, int num_elements, int *elements, int *p, Node *head) {
	int i, j; 

	i = 1;
	processEachPermutation(elements, num_elements, algorithm, head);

	while(i < num_elements) {
		if (p[i] < i) {
			j = i % 2 * p[i];
			swap(&elements[j], &elements[i]);
			p[i]++;
			i = 1;

			processEachPermutation(elements, num_elements, algorithm, head);

		} else {               
			p[i++] = 0;
		}
	}
}

void selection_sort(int *v, int n) {
 	for (int i = 0; i < n; i++) {
		int k = i;
		
		for (int j = i + 1; j < n; j++)
			if (less(v[j], v[k])) k = j;
		
		swap(&v[i], &v[k]);
	}
}

void insertion_sort(int *v, int n) {
	for (int i = 1; i < n; i++) {
		int key = v[i];
		int j = i - 1;

		while (j >= 0 && greater(v[j], key)) {
			v[j+1] = v[j];
			j--;
		}

		v[j+1] = key;
	}
}

void bubble_sort(int *v, int n) {
	for (int i = n-1; i > 0; i--)
		for (int j = 0; j < i; j++)
			if (greater(v[j], v[j+1]))
				swap(&v[j], &v[j+1]);
}

int separar(int *v, int p, int r) {
	int x = v[r], 
		i = p - 1, 
		j = 0;

	for (j = p; j < r; j++) {
		if (less(v[j], x)) {
			i++;
			swap(&v[i], &v[j]);
		}
	}

	swap(&v[i+1], &v[r]);

	return i + 1;
}

int separar_random(int *v, int p, int r) {
	int random = rand() % (r - p) + p;
	swap(&v[r], &v[random]);
	return separar(v, p, r);
}

void ep_quicksort(int *v, int p, int r, int random) {
	if (p < r) {
		int q = random == 1 ? separar_random(v, p, r) : separar(v, p, r);
		ep_quicksort(v, p, q - 1, random);
		ep_quicksort(v, q + 1, r, random);
	}
}

// Ordena no intervalo [p, q)
// Base da recursão: p >= (q - 1)
void ep_mergesort(int *v, int p, int q) {
	if (p < q - 1) {
		int r = (p + q) / 2;
		ep_mergesort(v, p, r);
		ep_mergesort(v, r+1, q);
		merge(v, p, r, q);
	}
}

void merge(int *v, int p, int q, int r) {
	int i, j, k, *aux;
	aux = malloc((r - p) * sizeof(int));
	i = p;
	j = q;
	k = 0;

	while (i < q && j < r) {
		if (greater(v[i], v[j])) aux[k++] = v[j++];
		else aux[k++] = v[i++];
	}

	while (i < q) aux[k++] = v[i++];
	while (j < r) aux[k++] = v[j++];
	
	for (i = p; i < r; i++) {
		v[i] = aux[i-p];
	}

	free(aux);
}

void heap_peneira(int *v, int p, int m) {
	int f = 2*p, x = v[p];
	
	while (f <= m) {
		if (f < m && less(v[f], v[f+1])) 
			f++;
		
		if (x >= v[f])
			break;
		
		v[p] = v[f];
		p = f;
		f = 2*p;
	}

	v[p] = x;
}

void ep_heapsort(int *v, int n) {
   int p, m;

	for (p = n/2; p >= 1; p--)
		heap_peneira(v, p, n);

	for (m = n; m >= 2; m--) {
		swap(&v[1], &v[m]);
		heap_peneira(v, 1, m-1);
	}
}