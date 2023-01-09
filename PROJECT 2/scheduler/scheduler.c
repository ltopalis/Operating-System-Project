#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "FCFS.h"
#include "SJF.h"
#include "RR.h"
#include "PRIO.h"
/* header files */

/* global definitions */

/* definition and implementation of process descriptor and queue(s) */

/* global variables and data structures */

/* signal handler(s) */

/* implementation of the scheduling policies, etc. batch(), rr() etc. */

int main(int argc, char **argv)
{
	/* local variables */
	process_list *root = (process_list *)malloc(sizeof(process_list));
	process_list *node = (process_list *)malloc(sizeof(process_list));

	root->next = NULL;
	root->prev = NULL;
	process_info data;

	data.elapsed_time = 1.01;
	strcpy(data.name, "work1");
	data.PID = 3627;
	data.priority = 6;
	data.workload_time = 1.01;
	RRadd(data, root);

	data.elapsed_time = 2.010;
	strcpy(data.name, "work2");
	data.PID = 3628;
	data.priority = 4;
	data.workload_time = 3.02;
	RRadd(data, root);

	data.elapsed_time = 3.010;
	strcpy(data.name, "work3");
	data.PID = 3639;
	data.workload_time = 6.03;
	data.priority = 1;
	RRadd(data, root);

	data.elapsed_time = 4.010;
	strcpy(data.name, "work4");
	data.PID = 3630;
	data.workload_time = 10.04;
	data.priority = 7;
	RRadd(data, root);

	data.elapsed_time = 5.010;
	strcpy(data.name, "work5");
	data.PID = 3631;
	data.workload_time = 15.05;
	data.priority = 3;
	RRadd(data, root);

	data.elapsed_time = 6.01;
	strcpy(data.name, "work6");
	data.PID = 3632;
	data.workload_time = 21.06;
	data.priority = 2;
	RRadd(data, root);

	data.elapsed_time = 7.01;
	strcpy(data.name, "work7");
	data.PID = 3633;
	data.workload_time = 28.07;
	data.priority = 5;
	RRadd(data, root);

	node = root->next;
	while (node->next != NULL)
	{
		node = node->next;
	}
	while (node != NULL)
	{
		toString(node->info);
		node = node->prev;
	}

	/* parse input arguments (policy, quantum (if required), input filename */

	/* read input file - populate queue */

	/* call selected scheduling policy */

	/* print information and statistics */

	printf("Scheduler exits\n");
	return 0;
}
