#ifndef __QUEUE_HEADER__
#define __QUEUE_HEADER__

#include "process.h"

struct process_node_struct {
	struct process_node_struct *next, *prev;
	Process *val;
};
typedef struct process_node_struct ProcessNode;

/* Create a node */
ProcessNode* create_node (Process *val, ProcessNode *prev, ProcessNode *next);

/* Create a queue */
ProcessNode* create_queue ();

/* Destroy a node */
void destroy_node (ProcessNode *node);

/* Destroy linked list */
void destroy_node_list (ProcessNode *head);

/* Insert on queue */
void insert_queue (ProcessNode *head, Process *process);

/* Pop on queue */
Process* pop_queue (ProcessNode *head);

#endif
