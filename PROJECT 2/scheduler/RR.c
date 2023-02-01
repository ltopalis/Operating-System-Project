#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>

#include "structures.h"
#include "RR.h"

/*
 * Η νέα διεργασία προστίθεται πάντα στο τέλος της λίστας.
 */
void RRadd(process_info data, process_list *root)
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

void RR(process_list *root, struct timespec quantum, process_list *finished)
{
    process_list *node = root->next;
    process_list *finished_node = finished;
    process_list *findingTheLastNode;
    history_data *history_node;
    int status;
    double start = 0.0, finish = 0.0;

    while (node != NULL)
    {
        if (!(node->info.PID = fork()))
        {
            // child
            char *arg[] = {node->info.name, NULL};
            execvp(arg[0], arg);
            perror("file not found");
            exit(1);
        }
        else
        {
            // DADDY
            start = get_wtime();
            // update the history of the very first process
            history_node = node->info.history;
            while (history_node->next != NULL)
            {
                history_node = history_node->next;
            }
            history_node->next = (history_data *)malloc(sizeof(history_data));
            strcpy(history_node->next->status, "RUNNING");
            history_node->next->time = time(NULL);
            history_node->next->next = NULL;

            while (root->next)
            {
                nanosleep(&quantum, NULL);
                if (kill(node->info.PID, SIGSTOP))
                    fprintf(stderr, "ERROR SENDING STOP MESSAGE\n");
                waitpid(node->info.PID, &status, WSTOPPED);

                if (WIFEXITED(status))
                {
                    // the process finished normally

                    // update history
                    history_node = node->info.history;
                    while (history_node->next != NULL)
                    {
                        history_node = history_node->next;
                    }
                    
                    history_node->next = (history_data *)malloc(sizeof(history_data));
                    strcpy(history_node->next->status, "EXITED");
                    history_node->next->time = time(NULL);
                    history_node->next->next = NULL;
                    node->info.workload_time = get_wtime() - node->info.workload_time;
                    finish = get_wtime();
                    node->info.elapsed_time += finish - start;

                    while (finished_node->next != NULL)
                    {
                        finished_node = finished_node->next;
                    }

                    // put the process to finished list

                    finished_node->next = node;
                    node->prev->next = node->next;
                    if (node->next != NULL)
                        node->next->prev = node->prev;
                    node->next = NULL;
                    node->prev = finished_node;

                    node = root->next;
                    if (node != NULL)
                    {
                        if (node->info.PID)
                        {
                            if (kill(node->info.PID, SIGCONT))
                                fprintf(stderr, "ERROR SENDING CONTINUE MESSAGE\n");
                            start = get_wtime();
                        }
                        else
                        {
                            start = get_wtime();
                            if (!(node->info.PID = fork()))
                            {
                                // only child comes here
                                char *arg[] = {node->info.name, NULL};
                                execvp(arg[0], arg);
                                perror("file not found");
                                exit(1);
                            }
                        }
                    }
                }
                else if (WIFSTOPPED(status))
                {
                    // the process stopped by a signal
                    
                    // update history
                    history_node = node->info.history;
                    while (history_node->next != NULL)
                    {
                        history_node = history_node->next;
                    }
                    history_node->next = (history_data *)malloc(sizeof(history_data));
                    strcpy(history_node->next->status, "STOPPED");
                    history_node->next->time = time(NULL);
                    history_node->next->next = NULL;
                    finish = get_wtime();
                    node->info.elapsed_time += (finish - start);

                    // put the process at the end of the list
                    if (node->next != NULL)
                    {
                        // There are more than one waiting processes
                        node->next->prev = node->prev;
                        node->prev->next = node->next;
                        findingTheLastNode = root->next;
                        while (findingTheLastNode->next != NULL)
                        {
                            findingTheLastNode = findingTheLastNode->next;
                        }
                        findingTheLastNode->next = node;
                        node->next = NULL;
                        node->prev = findingTheLastNode;
                    }

                    node = root->next;

                    if (node->info.PID)
                    {

                        if (kill(node->info.PID, SIGCONT))
                            fprintf(stderr, "ERROR SENDING CONTINUE MESSAGE\n");
                        start = get_wtime();
                    }
                    else
                    {
                        start = get_wtime();
                        if (!(node->info.PID = fork()))
                        {
                            // only child comes here
                            char *arg[] = {node->info.name, NULL};
                            execvp(arg[0], arg);
                            perror("file not found");
                            exit(1);
                        }
                    }

                    history_node = node->info.history;
                    while (history_node->next != NULL)
                    {
                        history_node = history_node->next;
                    }
                    history_node->next = (history_data *)malloc(sizeof(history_data));
                    strcpy(history_node->next->status, "RUNNING");
                    history_node->next->time = time(NULL);
                    history_node->next->next = NULL;
                }
            }
        }
    }
}
