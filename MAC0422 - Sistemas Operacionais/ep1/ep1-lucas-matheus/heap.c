#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include "heap.h"



/*
	===== ===== =====
	INTERNAL METHODS
	===== ===== =====
*/

static void swap (Process **a, Process **b) {
  Process *t = *a;
  *a = *b;
  *b = t;
}

static Process** init_pq (int initialSize) {
  Process **pq = malloc ((initialSize + 1) * sizeof (Process *));
	return pq;
}

static Process** resize_pq (Heap *heap) {
  int i;
  heap->size = 2 * heap->size;
  Process **new_pq = malloc (heap->size * sizeof (Process *));

	for (i = 1; i <= heap->n; i++) {
		new_pq[i] = heap->pq[i];
	}

  free(heap->pq);

  return new_pq;
}

static void swim (Heap *heap) {
  int t = heap->n;
  while (t > 1 && heap->pq[t/2]->remaining > heap->pq[t]->remaining) {
    swap (&(heap->pq[t/2]), &(heap->pq[t]));
    t /= 2;
  }
}

static void sink (Heap *heap) {
  int t = 1;
  while(2 * t <= heap->n) {
    int j = 2 * t;
    if (j < heap->n && (heap->pq[j]->remaining > heap->pq[j+1]->remaining)) j++;
    if (heap->pq[t]->remaining <= heap->pq[j]->remaining) break;
    swap (&(heap->pq[t]), &(heap->pq[j]));
    t = j;
  }
}



/*
	===== ===== =====
	EXTERNAL METHODS
	===== ===== =====
*/

/* Create a min heap */
Heap* create_heap () {
  Heap *heap = malloc (sizeof (struct heap_struct));
  heap->n = 0;
  heap->size = 1;
  heap->pq = init_pq (heap->size);
  return heap;
}

/* Insert in heap */
void insert_heap (Heap *heap, Process *a) {
	if (heap == NULL || a == NULL) return;

  if (heap->n == heap->size-1) {
		heap->pq = resize_pq (heap);
	}

  heap->pq[++(heap->n)] = a;
  swim (heap);
}

/* Get min and pop */
Process* pop_heap (Heap *heap) {
    if (heap->n <= 0) return NULL;
    swap (&(heap->pq[1]), &(heap->pq[heap->n]));
    Process *tmp = heap->pq[heap->n];
    heap->n--;
    sink (heap);
    /* free (heap->pq[heap->n+1]); */

    return tmp;
}

/* Destroy heap */
void destroy_heap (Heap *heap) {
    int i;

    for (i = 1; i <= heap->n; i++) {
      destroy_process (heap->pq[i]);
		}

    free (heap->pq);
    free (heap);
}
