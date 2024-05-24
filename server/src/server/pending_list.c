/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** pending_list
*/

#include "pending.h"
#include <stdlib.h>

pending_node_t *create_pending_node(pending_t *pending)
{
    pending_node_t *node = calloc(1, sizeof(pending_node_t));

    if (!node)
        return NULL;
    node->pending = pending;
    return node;
}

pending_list_t *create_pending_list(void)
{
    pending_list_t *head = calloc(1, sizeof(pending_list_t));

    if (!head)
        return NULL;
    LIST_INIT(head);
    return head;
}

void destroy_pending_node(pending_node_t *node)
{
    if (!node)
        return;
    destroy_pending(node->pending);
    free(node);
}

void destroy_pending_list(pending_list_t *list)
{
    pending_node_t *tmp = NULL;

    if (!list)
        return;
    while (!LIST_EMPTY(list)) {
        tmp = LIST_FIRST(list);
        LIST_REMOVE(tmp, entries);
        destroy_pending_node(tmp);
    }
    free(list);
}
