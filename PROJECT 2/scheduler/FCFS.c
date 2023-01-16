#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include "structures.h"
#include "FCFS.h"

/*
 * Η νέα διεργασία προστίθεται πάντα στο τέλος της λίστας.
 */
void FCFSadd(process_info data, process_list *root)
{
    process_list *node = root;

    while (node->next != NULL)
    {
        node = node->next;
    }

    node->next = (process_list *)malloc(sizeof(process_list));
    node->next->prev = node;
    node = node->next;
    copyInfoStructure(&(node->info), data);
    node->next = NULL;
}

void FCFS(process_list *root, process_list *finished)
{
    process_list *node = root->next;
    process_list *finished_node = finished;
    history_data *history_node;
    
    while (node != NULL)
    {
        node->info.elapsed_time = get_wtime();
        if (!(node->info.PID = fork()))
        {
            char *arg[] = {node->info.name, NULL};
            execvp(arg[0], arg);
            perror("file not found");
            exit(1);
        }
        else
        {
            history_node = node->info.history;
            while(history_node->next != NULL){
                history_node = history_node->next;
            }
            history_node->next = (history_data *)malloc(sizeof(history_data));
            strcpy(history_node->next->status, "RUNNING");
            //history_node->next->time = time(NULL);
            history_node->next->next = NULL;
            
            waitpid(node->info.PID, NULL, WUNTRACED);            
            history_node = node->info.history;
            while(history_node->next != NULL){
                history_node = history_node->next;
            }
            history_node->next = (history_data *)malloc(sizeof(history_data));
            strcpy(history_node->next->status, "EXITED");
            //history_node->next->time = time(NULL);
            history_node->next->next = NULL;

            node->info.workload_time = get_wtime() - node->info.workload_time;
            node->info.elapsed_time = get_wtime() - node->info.elapsed_time;

            

            while(finished_node->next != NULL){
                finished_node = finished_node->next;
            }
            
            finished_node->next = node;
            node->prev->next = node->next;
            if(node->next != NULL) node->next->prev = node->prev;
            node->next = NULL;
            node->prev = finished_node;

            node = root->next;
        }
    }
}