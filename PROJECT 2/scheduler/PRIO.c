#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include "PRIO.h"

// Δεδομένης μίας λίστας root ελέγχουμε το priority
// κάθε διεργασία και προστίθονται ταξινομημένες
// κατά αύξουσα σειρά
void PRIOadd(process_info data, process_list *root)
{
    process_list *node = root;
    process_list *adding_node = (process_list *)malloc(sizeof(process_list));
    copyInfoStructure(&(adding_node->info), data);

    while (node->next != NULL && node->next->info.priority <= data.priority)
    {
        node = node->next;
    }

    adding_node->next = node->next;
    adding_node->prev = node;
    if (node->next != NULL)
        node->next->prev = adding_node;
    node->next = adding_node;
}