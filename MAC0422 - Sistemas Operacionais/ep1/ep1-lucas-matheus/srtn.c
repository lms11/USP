/* Shortest Remaining Time Next */

#include <stdio.h>
#include <time.h>
#include "srtn.h"

static pthread_mutex_t mutex;
static unsigned int debugging = 1;

/* Some random calculation (keep CPU busy) */
static int bar () {
	int x = 0;
	x += 3 - 5;
	return x;
}

/* Process's job */
static void* foo (void *job) {
	pthread_mutex_lock (&mutex);

	Process *p = (Process *)job;

	if (debugging) {
		fprintf (stderr, "Job entering CPU: %s (%d) - t0: %lf | dt = %lf | r: %lf\n", p->name, p->id, p->t0, p->dt, p->remaining);
	}

	while (p->preemption == 0) {
		bar ();
	}

	if (debugging) {
		fprintf (stderr, "Job leaving CPU: %s (%d) - t0: %lf | dt = %lf | r: %lf\n", p->name, p->id, p->t0, p->dt, p->remaining);
	}

	p->preemption = 0;

	pthread_mutex_unlock (&mutex);

	return NULL;
}

/* Run a job */
static pthread_t runProcess (Process *job) {
	if (job == NULL) return NULL;

	pthread_t new_thread;

	if (pthread_create (&new_thread, NULL, foo, job)) {
		return new_thread;
	} else {
		return NULL;
	}
}

/* Check if there are new jobs available. Return the last available job. */
static ProcessNode* checkNewJobsIncoming (ProcessNode *lastAvailable, double timeElapsed, Heap *heap, unsigned int *anyNewProcess) {
	while (lastAvailable->next != NULL && lastAvailable->next->val->t0 <= timeElapsed) {
		lastAvailable = lastAvailable->next;

		if (debugging) {
			fprintf (stderr, "(t = %lf) Incoming job: %s (%d) - t0: %lf | dt = %lf | r: %lf\n", timeElapsed, lastAvailable->val->name, lastAvailable->val->id, lastAvailable->val->t0, lastAvailable->val->dt, lastAvailable->val->remaining);
		}

		insert_heap(heap, lastAvailable->val);

		*anyNewProcess = 1;
	}

	return lastAvailable;
}

void start_srtn (char *input_file, char *output_file, int debug) {
	debugging = debug;

	struct timeval initTime;
	struct timeval lastTime;
	gettimeofday(&initTime, NULL);
	gettimeofday(&lastTime, NULL);

	unsigned int jobsFinished = 0;
	unsigned int jobs = 0; /* Number of existing jobs */
	unsigned int contextChanges = 0;
	unsigned int anyNewProcess = 0; /* Flag if any new process */
	double timeElapsed = 0.0;
	double timeElapsedIteration; /* Time elapsed from last while iteration */

	Heap *heap = create_heap ();

	ProcessNode *head = readInput (input_file, &jobs);
	ProcessNode *lastAvailable = head;
	Process *currentJob = NULL;
	Process *previousJob = NULL;

	while (jobsFinished < jobs) {
		struct timeval now;
		gettimeofday(&now, NULL);

		timeElapsed = time_diff (now, initTime);
		timeElapsedIteration = time_diff (now, lastTime);

		if (currentJob != NULL && timeElapsedIteration >= currentJob->remaining) {
			/*
				=====
				Running job is done.
				=====
			*/
			jobsFinished++;

			/* Process finished */
			process_finished (currentJob);

			/* Print if debugging */
			if (debugging) {
				fprintf (stderr, "Job finished: %s (%d) - t0: %lf | dt = %lf | r: %lf\n", currentJob->name, currentJob->id, currentJob->t0, currentJob->dt, currentJob->remaining);
			}

			currentJob = previousJob = NULL;
		}

		anyNewProcess = 0;
		lastAvailable = checkNewJobsIncoming (lastAvailable, timeElapsed, heap, &anyNewProcess);

		/* If there are any new job, then we must recalculate which process to run */
		if (anyNewProcess) {
			previousJob = currentJob;

			if (currentJob != NULL) {
				previousJob->remaining -= timeElapsedIteration;
				gettimeofday(&lastTime, NULL);

				insert_heap (heap, currentJob);
			}
		}

		if (currentJob == NULL || anyNewProcess != 0) {
			/* Try to take another job (again) */
			currentJob = pop_heap (heap);

			if (currentJob != NULL && currentJob != previousJob) {
				/* Should change this job */

				/* First we alert old process to finish. */
				if (previousJob != NULL) {
					previousJob->preemption = 1;

					/* Context changed! Note: if doesn't have a previous, than it means: a) prev finished earlier; b) first job ever. */
					contextChanges++;
				}

				gettimeofday(&lastTime, NULL);
				runProcess (currentJob);

			}
		}
	}

	if (debugging) {
		fprintf (stderr, "Context changes: %u\n", contextChanges);
	}

	/* Write output */
	writeOutput (output_file, head, initTime, contextChanges);
}
