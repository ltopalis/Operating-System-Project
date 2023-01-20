#ifndef PRIO_H
#define PRIO_H

#include "structures.h"

void PRIOadd(process_info data, process_list *root);
void PRIO(process_list *root, struct timespec quantum, process_list *finished);

#endif