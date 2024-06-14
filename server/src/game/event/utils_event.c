/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** utils_event
*/

#include "game/event.h"
#include <stdlib.h>

bool add_event(event_list_t *event_list, event_t *event)
{
    event_node_t *event_node = create_event_node(event, 0.0);
    event_node_t *tmp = LIST_FIRST(event_list);

    if (!event_node)
        return false;
    if (!tmp) {
        LIST_INSERT_HEAD(event_list, event_node, entries);
        return true;
    } else {
        while (LIST_NEXT(tmp, entries))
            tmp = LIST_NEXT(tmp, entries);
        LIST_INSERT_AFTER(tmp, event_node, entries);
        return true;
    }
    return true;

}

uint get_event_list_size(event_list_t *head)
{
    uint size = 0;
    event_node_t *tmp = NULL;

    LIST_FOREACH(tmp, head, entries)
        size++;
    return size;
}