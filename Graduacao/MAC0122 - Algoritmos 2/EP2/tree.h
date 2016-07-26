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

/*
  algorithm.h

  Onde a mágica acontece. Aqui transformamos as etapas dos algoritmos em árvores.
*/

#ifndef __TREE_H__
#define __TREE_H__

typedef struct node_struct Node;
struct node_struct {
	struct node_struct *left, *right;
	double width; // largura da árvore em unidades de medida
	double x, y;
};

// Aloca e inicializa uma nova árvore
Node* createNode();


// Processa um dado algoritmo em todas as permutações possiveis (número de permutações: num_elements!)
Node* process(char algorithm[20], int num_elements);
void generatePermutations(char *algorithm, int num_elements, int *elements, int *p, Node *head);
void processEachPermutation(int *elements, int num_elements, char *algorithm, Node *head);


// Comparador customizado
int less(int a, int b);
int greater(int a, int b);
int qsort_compare_func(const void * a, const void * b); // Uso na qsort


// Algoritmos
void selection_sort(int *v, int n);
void insertion_sort(int *v, int n);
void bubble_sort(int *v, int n);
void ep_quicksort(int *v, int p, int r, int random); // sufixo ep_ para diferenciar da biblioteca padrão
void ep_mergesort(int *v, int p, int q); // sufixo ep_ para diferenciar da biblioteca padrão
void merge(int *v, int p, int q, int r);
void heap_peneira(int *v, int p, int m);
void ep_heapsort(int *v, int n); // sufixo ep_ para diferenciar da biblioteca padrão

#endif