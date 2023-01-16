#ifndef RR_H
#define RR_H

#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <sys/wait.h>
#include "structures.h"

void RRadd(process_info data, process_list *root);
void RR(process_list *root, struct timespec quantum, process_list *finished);

#endif