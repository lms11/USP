#include <stdio.h>
#include "fcfs.h"
#include "multiple_queues.h"
#include "srtn.h"

int main (int argc, char **argv) {
	/* Args: [ scheduler ] [ input file ] [ output file ] */

	if (argc < 4) {
		fprintf (stderr, "Usage: ./scheduler scheduler_id input_file output_file [-d -- optional]\n\n");
		return -1;
	}

	int debug = 0;

	if (argc >= 5 && (argv[4][0] == 'd' || argv[4][1] == 'd')) {
		debug = 1;
	}

	if (argv[1][0] == '1') {
		/* First-Come First-Served */
		start_fcfs (argv[2], argv[3], debug);

	} else if (argv[1][0] == '2') {
		/* Shortest Remaining Time Next */
		start_srtn (argv[2], argv[3], debug);

	} else if (argv[1][0] == '3') {
		/* Escalonamento com múltiplas filas */
		start_multiple_queues (argv[2], argv[3], debug);

	} else {
		fprintf (stderr, "Invalid scheduler. Use 1, 2 or 3.\n\n");
		return -1;

	}

	return 0;
}
