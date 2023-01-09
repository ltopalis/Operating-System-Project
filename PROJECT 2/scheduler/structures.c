#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "structures.h"

void copyInfoStructure(process_info *dest, process_info src){
    dest->elapsed_time = src.elapsed_time;
    dest->history = src.history;
    strcpy(dest->name, src.name);
    dest->PID = src.PID;
    dest->priority = src.priority;
    dest->workload_time = src.workload_time;
}

void toString(process_info node){
    fprintf(stdout, 
    "PID %d - CMD: %s\n                        Elapsed time = %.3f secs\n                        Workload time = %.3f secs\n",
    node.PID, node.name, node.elapsed_time, node.workload_time);
}

bool is_first(process_list node){
    if(node.prev->prev == NULL)
        return TRUE;
    return FALSE;
}