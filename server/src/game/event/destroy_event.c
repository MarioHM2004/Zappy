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

void destroy_event_node(event_node_t *en)
{
    if (!en)
        return;
    destroy_event(en->event);
    free(en);
}

void destroy_event_list(event_list_t *head)
{
    event_node_t *tmp = NULL;
    event_node_t *current = NULL;

    if (!head)
        return;
    current = LIST_FIRST(head);
    while (current != NULL) {
        tmp = LIST_NEXT(current, entries);
        LIST_REMOVE(current, entries);
        destroy_event_node(current);
        current = tmp;
    }
}
