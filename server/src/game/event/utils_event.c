/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** utils_event
*/

#include "game/event.h"
#include <stdlib.h>

uint get_event_list_size(event_list_t *head)
{
    uint size = 0;
    event_node_t *tmp = NULL;

    LIST_FOREACH(tmp, head, entries)
        size++;
    return size;
}