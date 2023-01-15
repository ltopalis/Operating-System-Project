#ifndef FCFS_H
#define FCFS_H

#include "structures.h"

void FCFSadd(process_info data, process_list *root);
void FCFS(process_list *root, process_list *finished);

#endif