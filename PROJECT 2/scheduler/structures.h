/*
 * ΣΑΜΑΡΑ ΧΡΙΣΤΙΝΑ-ΕΛΕΑΝΝΑ 1084622
 * ΤΟΠΑΛΗΣ ΛΑΖΑΡΟΣ         1088101
 */

#ifndef STRUCTURES_H
#define STRUCTURES_H

#define TRUE 1
#define FALSE 0

#include <stdbool.h>
#include <time.h>
#include <sys/time.h>

struct history_data
{
    char status[20];
    time_t time;
    struct history_data *next;
};

struct process_info
{
    int PID;
    char name[20];
    double elapsed_time;
    double workload_time;
    int priority;
    struct history_data *history;
};

struct process_list
{
    struct process_list *prev;
    struct process_info info;
    struct process_list *next;
};

typedef struct history_data history_data;
typedef struct process_info process_info;
typedef struct process_list process_list;

void copyInfoStructure(process_info *dest, process_info src);
void toString(process_info node, FILE *file);
bool is_first(process_list node);
void print_to_file(process_list *root, int argc, char **argv);
double get_wtime(void);

#endif