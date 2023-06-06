/*
** EPITECH PROJECT, 2023
** B-PDG-300-MAR-3-1-PDGD04pm-erwan.gonzales
** File description:
** list_del_elem_at_front
*/

#include "list.h"
#include <stdlib.h>

bool list_del_elem_at_front(list_t *front_ptr)
{
    if (*front_ptr == NULL)
        return false;
    list_t head = *front_ptr;
    list_t buff = head->next;
    if (buff != NULL)
        buff->prev = head->prev;
    if (head->prev != NULL)
        head->prev->next = buff;
    free(head);
    *front_ptr = buff;
    return true;
}
