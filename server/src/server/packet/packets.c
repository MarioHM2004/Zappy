/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** packets
*/

#include "server/packet.h"
#include <stdlib.h>
#include <string.h>

packet_t *create_packet(const char *data)
{
    packet_t *packet = calloc(1, sizeof(packet_t));

    if (!packet)
        return NULL;
    packet->data = calloc(strlen(data) + 1, sizeof(char));
    if (!packet->data) {
        free(packet);
        return NULL;
    }
    strcpy(packet->data, data);
    return packet;
}

packet_node_t *create_packet_node(packet_t *p)
{
    packet_node_t *node = calloc(1, sizeof(packet_node_t));

    if (!node)
        return NULL;
    node->packet = p;
    return node;
}

packet_list_t *create_packet_list(void) {
    packet_list_t *list = calloc(1, sizeof(packet_list_t));

    if (!list)
        return NULL;
    LIST_INIT(list);
    return list;
}
