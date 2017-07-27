#include <stdlib.h>
#include <string.h>
#include "process.h"

Process* create_process(int id, double t0, char name[100], double dt, double deadline) {
	/* Get some memory space for our struct */
	Process *new_process = malloc(sizeof (struct process_struct));

	/* Copy data */
	new_process->id = id;
	new_process->t0 = t0;
	new_process->dt = dt;
	new_process->deadline = deadline;

	/* Set initial value */
	new_process->preemption = 0;
	new_process->done = 0;
	new_process->remaining = dt;
	new_process->quantum = CONST_QUANTUM;

	/* Copy name string into struct */
	strcpy(new_process->name, name);

	return new_process;
}

void destroy_process(Process *p) {
	/*
	* Destroy thread if exists *
	if (p->thread_id != NULL) {
		* TODO: destroy thread *
	}

	* Destroy mutex if exists *
	if (p->mutex_id != NULL) {
		* TODO: destroy mutex *
	}
	*/

	free(p);
}

/* Job finished */
void process_finished (Process *process) {
	process->done = 1;
	process->remaining = 0;

	/* Set finishedAt time */
	gettimeofday(&(process->finishedAt), NULL);

	/* Alert process to finish. */
	process->preemption = 1;
}
