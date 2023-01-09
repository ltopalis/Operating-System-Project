#include <stdio.h>
#include <string.h>
#include "structures.h"
#include "FCFS.h"
/* header files */

/* global definitions */

/* definition and implementation of process descriptor and queue(s) */

/* global variables and data structures */

/* signal handler(s) */

/* implementation of the scheduling policies, etc. batch(), rr() etc. */

int main(int argc, char **argv)
{
	/* local variables */
	process_list root;
	process_list *node;

	process_info newInfo;
	newInfo.elapsed_time = 111.02;
	newInfo.history = NULL;
	strcpy(newInfo.name, "k");
	newInfo.PID = 1520;
	newInfo.priority = 1;
	newInfo.workload_time = 752.5;
	
	process_list newP;
	newP.info = newInfo;

	add(&newP, root);

	node = &root;
	printf("%p %p", &root, root.next);
	while(node != NULL){
		printf("%s\n", node->info.name);
        node = node->next;
    }


	/* parse input arguments (policy, quantum (if required), input filename */

	/* read input file - populate queue */

	/* call selected scheduling policy */

	/* print information and statistics */

	printf("Scheduler exits\n");
	return 0;
}
