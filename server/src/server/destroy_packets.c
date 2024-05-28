/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** destroy_packets
*/

#include "server/server.h"

void destroy_packet(packet_t *packet)
{
    if (!packet)
        return;
    free(packet);
}

void destroy_packet_node(packet_node_t *pn)
{
    if (!pn)
        return;
    if (pn->packet)
        destroy_packet(pn->packet);
    free(pn);
}

void destroy_packet_list(packet_list_t *head)
{
    packet_node_t *tmp = NULL;
    packet_node_t *current = NULL;

    if (!head)
        return;
    current = LIST_FIRST(head);
    while (current != NULL) {
        tmp = LIST_NEXT(current, entries);
        LIST_REMOVE(current, entries);
        destroy_packet_node(current);
        free(current);
        current = tmp;
    }
}
