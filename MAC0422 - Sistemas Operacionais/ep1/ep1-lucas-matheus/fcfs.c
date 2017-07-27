/* First-Come First-Served */

#include <stdio.h>
#include <time.h>
#include "fcfs.h"

static pthread_mutex_t mutex;
static unsigned int debugging = 0;

/* Some random calculation (keep CPU busy) */
static int bar () {
	int x = 42;
	x += 3 - 5;
	return x;
}

/* Process's job */
static void* foo (void *job) {
	pthread_mutex_lock (&mutex);

	Process *p = ((ProcessNode *)job)->val;

	if (debugging) {
		fprintf (stderr, "Job entering CPU: %s (%d) - t0: %lf | dt = %lf | r: %lf | q: %lf\n", p->name, p->id, p->t0, p->dt, p->remaining, p->quantum);
	}

	while (p->preemption == 0) {
		bar ();
	}

	if (debugging) {
		fprintf (stderr, "Job leaving CPU: %s (%d) - t0: %lf | dt = %lf | r: %lf | q: %lf\n", p->name, p->id, p->t0, p->dt, p->remaining, p->quantum);
	}

	p->preemption = 0;

	pthread_mutex_unlock (&mutex);

	return NULL;
}

/* Run a job */
static pthread_t runProcess (ProcessNode *job) {
	if (job == NULL || job->val == NULL) return NULL;

	pthread_t new_thread;

	if (pthread_create (&new_thread, NULL, foo, job)) {
		return new_thread;
	} else {
		return NULL;
	}
}

/* Check if there are new jobs available. Return the last available job. */
static ProcessNode* checkNewJobsIncoming (ProcessNode *lastAvailable, double timeElapsed) {
	while (lastAvailable->next != NULL && lastAvailable->next->val->t0 <= timeElapsed) {
		lastAvailable = lastAvailable->next;

		fprintf (stderr, "(t = %lf) Incoming job:\n", timeElapsed);
		printProcess (lastAvailable->val);
	}

	return lastAvailable;
}

static ProcessNode* getNextAvailableJob (ProcessNode *head, double timeElapsed) {
	ProcessNode *cur = head->next;
	while (cur != NULL && cur->val->done == 1) {
		cur = cur->next;
	}

	if (cur != NULL && cur->val->t0 <= timeElapsed) {
		return cur;

	} else {
		return NULL;

	}
}

void start_fcfs (char *input_file, char *output_file, int debug) {
	debugging = debug;

	struct timeval initTime;
	struct timeval lastTime;
	gettimeofday(&initTime, NULL);
	gettimeofday(&lastTime, NULL);

	unsigned int jobsFinished = 0;
	unsigned int jobs = 0; /* Number of existing jobs */
	unsigned int contextChanges = 0; /* Always 0 for this algorithm. See: http://paca.ime.usp.br/mod/forum/discuss.php?d=32063 */
	double timeElapsed = 0.0;
	double timeElapsedIteration; /* Time elapsed from last while iteration */

	ProcessNode *head = readInput (input_file, &jobs);
	ProcessNode *lastAvailable = head;
	ProcessNode *currentJob = NULL;

	while (jobsFinished < jobs) {
		struct timeval now;
		gettimeofday(&now, NULL);

		timeElapsed = time_diff (now, initTime);
		timeElapsedIteration = time_diff (now, lastTime);

		if (debugging) {
			lastAvailable = checkNewJobsIncoming (lastAvailable, timeElapsed);
		}

		if (currentJob != NULL && timeElapsedIteration >= currentJob->val->dt) {
			/*
				=====
				Running job is done.
				Let's take another job to work.
				=====
			*/
			jobsFinished++;

			/* Process finished */
			process_finished (currentJob->val);

			/* Print if debugging */
			if (debugging) {
				fprintf (stderr, "Job finished: %s (trace line: %d)\n", currentJob->val->name, currentJob->val->id);
			}

			/* Try to take another job */
			currentJob = getNextAvailableJob (head, timeElapsed);

			/* Run the next job */
			gettimeofday(&lastTime, NULL);
			runProcess (currentJob);

		} else if (currentJob == NULL) {
			/* Try to take another job (again) */
			currentJob = getNextAvailableJob (head, timeElapsed);

			/* Run the next job */
			gettimeofday(&lastTime, NULL);
			runProcess (currentJob);

		}
	}

	if (debugging) {
		fprintf (stderr, "Context changes: %u\n", contextChanges);
	}

	/* Write output */
	writeOutput (output_file, head, initTime, contextChanges);
}
