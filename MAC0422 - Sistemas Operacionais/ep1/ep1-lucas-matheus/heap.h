#ifndef __HEAP_HEADER__
#define __HEAP_HEADER__

#include "process.h"

struct heap_struct {
    Process **pq;
    int n, size;
};
typedef struct heap_struct Heap;

/* Create a min heap */
Heap* create_heap ();

/* Insert in heap */
void insert_heap (Heap *heap, Process *a);

/* Get min and pop */
Process* pop_heap (Heap *heap);

/* Destroy heap */
void destroy_heap (Heap *heap);

#endif
