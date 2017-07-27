#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "input.h"

/* Read input from stdin */
ProcessNode* readInput (char *input_file, unsigned int *jobs) {
	FILE *input = fopen (input_file, "r+");

	if (input == NULL) {
		fprintf (stderr, "Failed to open input file.\n");
		exit (1);
	}

	ProcessNode *head = create_node (NULL, NULL, NULL);

  double tmp_t0, tmp_dt, tmp_deadline;
	char tmp_name[100];
	unsigned int id = 0;

  while (fscanf (input, " %lf", &tmp_t0) != EOF) {
    fscanf(input, " %s %lf %lf", tmp_name, &tmp_dt, &tmp_deadline);

		Process *process = create_process (++id, tmp_t0, tmp_name, tmp_dt, tmp_deadline);
    insert_queue (head, process); /* TODO: improve this. O(n) on insert -> O(1) */

		/* Clean tmp name */
		memset (tmp_name, 0, sizeof (tmp_name));
  }

	/* Number of jobs */
	*jobs = id;

	return head;
}

/* Print linked list */
void writeOutput (char *input_file, ProcessNode *head, struct timeval initTime, unsigned int contextChanges) {
	FILE *output = fopen (input_file, "w");
	unsigned int total = 0, done = 0;

	if (output == NULL) {
		fprintf (stderr, "Failed to open output file.\n");
		exit (1);
	}

	while (head->next != NULL) {
		head = head->next;

		if (head->val != NULL) {
			Process *p = head->val;

			total++;
			if (time_diff (p->finishedAt, initTime) <= p->deadline) done++;

			fprintf (output, "%s %lf %lf\n", p->name, time_diff (p->finishedAt, initTime), time_diff (p->finishedAt, initTime) - p->t0);
		}
	}

	fprintf(output, "%u\n", contextChanges);
}

/* Print process */
void printProcess (Process *p) {
	fprintf (stderr, "[PROCESS] Trace line: %d | name = %s | t0 = %f | dt = %f | deadline = %f | remaining = %f\n", p->id, p->name, p->t0, p->dt, p->deadline, p->remaining);
}

/* Elapsed time */
double time_diff(struct timeval t2, struct timeval t1) {
	return 1.0 * ((t2.tv_usec + 1000000 * t2.tv_sec) - (t1.tv_usec + 1000000 * t1.tv_sec)) / 1000000.0;
}
