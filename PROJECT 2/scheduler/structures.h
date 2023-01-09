#ifndef STRUCTURES_H
#define STRUCTURES_H

#define TRUE 1
#define FALSE 0

#include <stdbool.h>

struct history_data{
    float time;
    char status[20];
    struct history_data *next;
};

struct process_info{
    int PID;
    char name[20];
    float elapsed_time;
    float workload_time;
    int priority;
    struct history_data *history;
};

struct process_list{
    struct process_list *prev;
    struct process_info info;
    struct process_list *next;
};

typedef struct history_data history_data;
typedef struct process_info process_info;
typedef struct process_list process_list;

void copyInfoStructure(process_info *dest, process_info src);
void toString(process_info node);
bool is_first(process_list node);

#endif