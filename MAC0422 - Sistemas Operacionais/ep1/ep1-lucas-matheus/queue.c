#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input.h"

/* Create a node */
ProcessNode* create_node (Process *val, ProcessNode *prev, ProcessNode *next) {
	ProcessNode *new_node = malloc (sizeof (struct process_node_struct));
	new_node->val = val;
	new_node->next = next;
	new_node->prev = prev;

	return new_node;
}

/* Create a queue */
ProcessNode* create_queue () {
	return create_node (NULL, NULL, NULL);
}

/* Destroy a node */
void destroy_node (ProcessNode *node) {
	/* Link prev with next */
	if (node->prev != NULL) {
		node->prev->next = node->next;
	}

	/* Destroy associated process */
	if (node->val != NULL) {
		destroy_process (node->val);
	}
}

/* Destroy linked list */
void destroy_node_list (ProcessNode *head) {
	if (head == NULL) return;

	/* Como eu curto recursão, cara (quando eu entendo) */
	destroy_node_list (head->next);
	destroy_node (head);
}

/* Insert on queue */
void insert_queue (ProcessNode *head, Process *process) {
	ProcessNode *cur = head;
	while (cur->next != NULL) {
		cur = cur->next;
	}

	cur->next = create_node (process, cur, NULL);
}

/* Pop on queue */
Process* pop_queue (ProcessNode *head) {
	ProcessNode *retNode = head->next;

	if (retNode != NULL) {
		head->next = retNode->next;
		retNode->prev = head;

		Process *retVal = retNode->val;

		/* TODO: leak here? destroy_node (retNode); */

		return retVal;

	} else {
		return NULL;

	}
}
