#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include "PRIO.h"
#include "FCFS.h"
#include "RR.h"

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

void PRIO(process_list *root, struct timespec quantum, process_list *finished)
{
    process_list *node = root;
    int array_size;

    while (node->next != NULL)
    {
        node = node->next;
    }

    array_size = node->info.priority + 1;
    process_list *array_list[array_size];

    for (int i = 0; i < array_size; i++)
    {
        array_list[i] = (process_list *)malloc(sizeof(process_list));
    }

    /*
        κάθε στοιχείο της λίστας τοποθετείται
        σε ένα κελί του πίνακα σύμφωνα με το
        priority του
    */

    while (root->next != NULL)
    {
        int index = root->next->info.priority;
        process_list *current_node = root->next;
        process_list *temp_node = array_list[index];

        while (temp_node->next != NULL)
        {
            temp_node = temp_node->next;
        }

        temp_node->next = current_node;
        if (current_node->next != NULL)
            current_node->next->prev = root;
        root->next = current_node->next;
        current_node->next = NULL;
        current_node->prev = temp_node;
    }

    /*for (int i = 1; i < array_size; i++)
    {
        printf("%d\n", i);

        process_list *current_node = array_list[i]->next;
        while (current_node != NULL)
        {
            printf("\t%d\n", current_node->info.priority);
            current_node = current_node->next;
        }
    }*/

    for (int i = 1; i < array_size; i++)
    {
        if (array_list[i]->next != NULL)
        {
            if (array_list[i]->next->next == NULL)
            {
                FCFS(array_list[i], finished);
            }
            else
            {
                RR(array_list[i], quantum, finished);
            }
        }
    }

    for(int i = 0; i < array_size; i++)
        free(array_list[i]);
}