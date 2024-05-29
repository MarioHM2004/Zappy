/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** destroy_event
*/

#include "game/event.h"

#include <stdlib.h>

event_t *create_event(event_type_e type, void *data, size_t size)
{
    event_t *event = calloc(1, sizeof(event_t));

    if (!event)
        return NULL;
    event->type = type;
    event->size = size;
    if (event->type == BROADCAST)
        event->data.broadcast = *(broadcast_t *)data;
    else
        event->data.player = *(player_t *)data;
    return event;
}

event_node_t *create_event_node(event_t *e)
{
    event_node_t *node = calloc(1, sizeof(event_node_t));

    if (!node)
        return NULL;
    node->event = e;
    return node;
}

event_list_t *create_event_list(void)
{
    event_list_t *head = calloc(1, sizeof(event_list_t));

    if (!head)
        return NULL;
    LIST_INIT(head);
    return head;
}
