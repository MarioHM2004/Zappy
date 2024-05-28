/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** send_packets
*/

#include "server/server.h"

void write_packets(socket_t *socket, packet_list_t **packets)
{
    packet_node_t *tmp = NULL;

    if (!packets)
        return;
    LIST_FOREACH(tmp, *packets, entries) {
        if (!tmp->packet)
            continue;
        write_socket(socket, tmp->packet);
    }
    destroy_packet_list(*packets);
    *packets = create_packet_list();
    client->socket->mode = READ;
}
