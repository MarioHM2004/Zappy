/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** destroy_event
*/

#include "game/event.h"
#include <stdlib.h>

void destroy_event(event_t *event)
{
    if (!event)
        return;
    free(event);
}

void destroy_event_node(event_node_t *node)
{
    if (!node)
        return;
    destroy_event(node->event);
    free(node);
}

void destroy_event_list(event_list_t *list)
{
    event_node_t *tmp = NULL;

    if (!list)
        return;
    while (!LIST_EMPTY(list)) {
        tmp = LIST_FIRST(list);
        LIST_REMOVE(tmp, entries);
        destroy_event_node(tmp);
    }
    free(list);
}