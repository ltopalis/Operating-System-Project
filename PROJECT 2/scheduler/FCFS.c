#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "structures.h"
#include "FCFS.h"

/*
 * Η νέα διεργασία προστίθεται πάντα στο τέλος της λίστας.
*/
void add(process_list *data, process_list root){
    process_list *node = &root;
    while(node->next != NULL){
        node = node->next;
    }

    node->next = (process_list *)malloc(sizeof(process_list));
    node->next = data;
    data->prev = node;
    data->next = NULL;
    printf("In add %p %p %p\n", node, node->next, node->next->next);
    node = &root;
    while(node->next != NULL){
        printf("%s\n", node->info.name);
        node = node->next;
    }
}

bool is_first(process_list node){
    if(node.prev->prev == NULL)
        return TRUE;
    return FALSE;
}