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
	process_info data;
	process_list *root = (process_list *)malloc(sizeof(process_list));
	process_list *node = (process_list *)malloc(sizeof(process_list));
	root->next = NULL;
	root->prev = NULL;

	/* choosing algorithm */

	if (!strcmp(argv[1], "FCFS"))
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
		data.workload_time = clock();
		data.elapsed_time = 0;
		data.PID = 0;
		data.history = (history_data *)malloc(sizeof(history_data));
		strcpy(data.history->status, "Initialize");
		data.history->time = time(NULL);
		data.history->next = NULL;
		(*algorithm)(data, root);
	}

	if (!strcmp(argv[1], "FCFS"))
	{
		FCFS(root);
	}
	else if (!strcmp(argv[1], "SJF"))
	{
		FCFS(root);
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










	fclose(fp);
	if (line)
	{
		free(line);
	}

	/* print the list */
	node = root->next;
	while (node != NULL)
	{
		toString(node->info);
		history_data *hid = (history_data *)malloc(sizeof(history_data));
		hid = node->info.history;
		while (hid != NULL)
		{
			printf("%s: %s\n", hid->status, ctime(&hid->time));
			hid = hid->next;
		}

		node = node->next;
	}

	printf("Scheduler exits\n");
	exit(0);
}
