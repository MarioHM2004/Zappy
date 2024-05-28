/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** gui_list
*/

#include "server/gui.h"
#include "server/packet.h"


gui_node_t *create_gui_node(gui_t *gui)
{
    gui_node_t *node = calloc(1, sizeof(gui_node_t));

    if (!node)
        return NULL;
    node->gui = gui;
    return node;
}

gui_list_t *create_gui_list(void)
{
    gui_list_t *head = calloc(1, sizeof(gui_list_t));

    if (!head)
        return NULL;
    LIST_INIT(head);
    return head;
}

void destroy_gui_node(gui_node_t *node)
{
    if (!node)
        return;
    destroy_client(node->gui);
    free(node);
}

void destroy_gui_list(gui_list_t *list)
{
    gui_node_t *tmp = NULL;
    gui_node_t *current = NULL;

    if (!list)
        return;
    current = LIST_FIRST(list);
    while (current != NULL) {
        tmp = LIST_NEXT(current, entries);
        LIST_REMOVE(current, entries);
        destroy_packet_node(current);
        free(current);
        current = tmp;
    }
}