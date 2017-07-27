#ifndef __PROCESS_HEADER__
#define __PROCESS_HEADER__

#include <pthread.h>
#include <sys/time.h>

#define CONST_QUANTUM 0.1

struct process_struct {
    double t0;
    char name[100];
    double dt;
    double deadline;
    double remaining;
		double quantum;
		unsigned int preemption;
		unsigned int done;

		/* Stat info */
		unsigned int id; /* Number of line in trace */
		struct timeval finishedAt;
};
typedef struct process_struct Process;

/* Create a new process */
Process* create_process(int id, double t0, char name[100], double dt, double deadline);

/* Destroy a process */
void destroy_process(Process *p);

/* Job finished */
void process_finished (Process *process);

#endif
