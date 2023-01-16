#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/time.h>
#include "structures.h"

void copyInfoStructure(process_info *dest, process_info src)
{
    dest->elapsed_time = src.elapsed_time;
    dest->history = src.history;
    strcpy(dest->name, src.name);
    dest->PID = src.PID;
    dest->priority = src.priority;
    dest->workload_time = src.workload_time;
}

void toString(process_info node, FILE *file)
{
    char *name, *token;
    token = strtok(node.name, "/");
    while (token != NULL)
    {
        name = token;
        token = strtok(NULL, "/");
    }
    fprintf(file,
            "PID %d - CMD: %s\n\t\t\t\t\t\t%-13s = %.3lf secs\n\t\t\t\t\t\t%-13s = %.3lf secs\n",
            node.PID, name, "Elapsed time", node.elapsed_time, "Workload time", node.workload_time);
}

bool is_first(process_list node)
{
    if (node.prev->prev == NULL)
        return TRUE;
    return FALSE;
}

void print_to_file(process_list *root, int argc, char **argv)
{
    FILE *output, *history_output;
    struct stat st;
    char *name, *token;
    double workload = 0.0;
    process_list *node = (process_list *)malloc(sizeof(process_list));

    if (stat("output", &st))
        if (mkdir("output", 0777))
        {
            perror("mkdir failed");
            exit(0);
        }
    if (!(output = fopen("output/output.txt", "a")))
    {
        fprintf(stderr, "File can't be open!\n");
        exit(0);
    }
    if (!(history_output = fopen("output/history.txt", "a")))
    {
        fprintf(stderr, "File can't be open!\n");
        exit(0);
    }

    fprintf(output, "# ");
    for (int i = 0; i < argc; i++)
    {
        fprintf(output, "%s ", argv[i]);
        fprintf(history_output, "%s \n", argv[i]);
    }
    fprintf(output, "\n\n");

    node = root->next;
    while (node != NULL)
    {
        toString(node->info, output);
        workload += node->info.elapsed_time;
        history_data *hid = (history_data *)malloc(sizeof(history_data));
        token = strtok(node->info.name, "/");
        while (token != NULL)
        {
            name = token;
            token = strtok(NULL, "/");
        }
        fprintf(history_output, "%s (%d)\n", name, node->info.PID);
        hid = node->info.history;
        while (hid != NULL)
        {
            fprintf(history_output, "\t\t%-7s\n", hid->status/*, ctime(&hid->time)*/);
            hid = hid->next;
        }

        node = node->next;
    }
    fprintf(output, "WORKLOAD TIME: %.3lf seconds\n\n", workload);
    fprintf(history_output, "\n\n");
    fclose(output);
    fclose(history_output);
}

double get_wtime(void)
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1.0e-6;
}