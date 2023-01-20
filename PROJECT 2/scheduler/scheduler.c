#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
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
	void (*algorithm)(process_info, process_list *);
	char *line = NULL;
	size_t len = 0;
	FILE *fp;
	struct timespec quantum;
	process_info data;
	process_list *root = (process_list *)malloc(sizeof(process_list));
	process_list *finished = (process_list *)malloc(sizeof(process_list));
	root->next = NULL;
	root->prev = NULL;
	finished->next = NULL;
	finished->prev = NULL;

	/* choosing algorithm */

	if (!strcmp(argv[1], "FCFS") || !strcmp(argv[1], "BATCH"))
	{
		algorithm = &FCFSadd;
	}
	else if (!strcmp(argv[1], "SJF"))
	{
		algorithm = &SJFadd;
	}
	else if (!strcmp(argv[1], "RR"))
	{
		algorithm = &RRadd;
	}
	else if (!strcmp(argv[1], "PRIO"))
	{
		algorithm = &PRIOadd;
	}
	else
	{
		fprintf(stderr, "Wrong Argument\n");
		exit(0);
	}

	/* read the file and initialize the list */
	if (!(fp = fopen(argv[argc - 1], "r")))
	{
		fprintf(stderr, "File can't be open!\n");
		exit(0);
	}

	while (getline(&line, &len, fp) != -1)
	{
		strcpy(data.name, strtok(line, "\t"));
		data.priority = atoi(strtok(NULL, "\t"));
		data.workload_time = get_wtime();
		data.elapsed_time = 0.0;
		data.PID = 0;
		data.history = (history_data *)malloc(sizeof(history_data));
		strcpy(data.history->status, "READY");
		data.history->time = time(NULL);
		data.history->next = NULL;
		(*algorithm)(data, root);
	}

	if (!strcmp(argv[1], "FCFS") || !strcmp(argv[1], "BATCH"))
	{
		FCFS(root, finished);
	}
	else if (!strcmp(argv[1], "SJF"))
	{
		FCFS(root, finished);
	}
	else if (!strcmp(argv[1], "RR"))
	{
		long temp = strtol(argv[2], NULL, 10);
		quantum.tv_sec = temp / 1000000000;
		quantum.tv_nsec = temp % 1000000000;
		RR(root, quantum, finished);
	}
	else if (!strcmp(argv[1], "PRIO"))
	{
		long temp = strtol(argv[2], NULL, 10);
		quantum.tv_sec = temp / 1000000000;
		quantum.tv_nsec = temp % 1000000000;
		PRIO(root, quantum, finished);
	}
	else
	{
		fprintf(stderr, "Wrong Argument\n");
		exit(0);
	}

	fclose(fp);
	if (line)
	{
		free(line);
	}

	/* print the list */
	print_to_file(finished, argc, argv);

	printf("Scheduler exits\n");
	exit(0);
}
