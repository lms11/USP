#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

Stack stack_init() {
	Stack s = malloc(sizeof(StackItem));

	// Init
	if (s) {
		s->size = 0;
		s->next = NULL;
	}

	return s;
}

void stack_destroy(Stack s) {
	if (!s) return; // Stop if s is already null

	// Release all stack's items
	Stack cur = s->next, next = cur->next;
	while (next != NULL) {
		free(cur);
		cur = next;
		next = cur->next;
	}
	free(cur);
	free(s);
}

int stack_push(Stack s, double val) {
	if (!s) return 0; // Stop if s is already null

	// Alloc and init StackItem
	Stack item = malloc(sizeof(StackItem));

	// Check if item was successfully allocated
	if (!item) {
		return 0;
	}

	item->value = val;
	item->next = s->next;
	s->next = item;

	// Update stack's size
	s->size++;

	return 1;
}

double stack_pop(Stack s) {
	Stack item;
	double value;
	if (!s || s->size == 0) return 0.0; // Stop if s is already null or empty

	item = s->next;
	value = item->value;

	s->next = item->next;

	// Update stack's size
	s->size--;

	free(item);

	return value;
}

int stack_size(Stack s) {
	if (!s) return -1;
	else return s->size;
}
