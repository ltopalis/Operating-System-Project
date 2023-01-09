#ifndef FCFS_H
#define FCFS_H

#include <stdbool.h>
#include "structures.h"

#define TRUE 1
#define FALSE 0

void FCFSadd(process_info data, process_list *root);
bool is_first(process_list node);

#endif