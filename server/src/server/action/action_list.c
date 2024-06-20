/*
** EPITECH PROJECT, 2024
** action
** File description:
** action_list
*/

#include "server/action.h"
#include <stdlib.h>
#include <sys/queue.h>

action_node_t *create_action_node(action_t *a)
{
    action_node_t *node = calloc(1, sizeof(action_node_t));

 if (!node)
        return NULL;
    node->action = a;
    return node;
}

action_list_t *create_action_list(void)
{
    action_list_t *head = calloc(1, sizeof(action_list_t));

    if (!head)
        return NULL;
    LIST_INIT(head);
    return head;
}

void destroy_action_node(action_node_t *an)
{
    if (!an)
        return;
    destroy_action(an->action);
    free(an);
}

void destroy_action_list(action_list_t *head)
{
    action_node_t *tmp = NULL;
    action_node_t *current = NULL;

    if (!head)
        return;
    current = LIST_FIRST(head);
    while (current) {
        tmp = LIST_NEXT(current, entries);
        LIST_REMOVE(current, entries);
        destroy_action_node(current);
        current = tmp;
    }
    free(head);
}

static void insert_tail(action_list_t *actions, action_node_t *node)
{
    action_node_t *tmp = NULL;

    if (!LIST_FIRST(actions)) {
        LIST_INSERT_HEAD(actions, node, entries);
        return;
    }
    tmp = LIST_FIRST(actions);
    while (LIST_NEXT(tmp, entries))
        tmp = LIST_NEXT(tmp, entries);
    LIST_INSERT_AFTER(tmp, node, entries);
}

void add_action(action_list_t *head, action_t *action)
{
    action_node_t *node = NULL;

    if (!head || !action)
        return;
    node = create_action_node(action);
    if (!node)
        return;
    insert_tail(head, node);
}

