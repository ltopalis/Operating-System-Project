#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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