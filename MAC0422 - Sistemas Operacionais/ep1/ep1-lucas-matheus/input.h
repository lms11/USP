#ifndef __INPUT_HEADER__
#define __INPUT_HEADER__

#include "process.h"
#include "queue.h"

/* Read input from stdin */
ProcessNode* readInput (char *input_file, unsigned int *jobs);

/* Print linked list */
void writeOutput (char *input_file, ProcessNode *head, struct timeval initTime, unsigned int contextChanges);

/* Print process */
void printProcess (Process *p);

/* Elapsed time */
double time_diff (struct timeval t2, struct timeval t1);

#endif
