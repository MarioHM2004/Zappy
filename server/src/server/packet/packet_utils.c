/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** send_packets
*/

#include "server/packet.h"
#include "server/server.h"
#include <string.h>
#include <sys/queue.h>

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
    socket->mode = READ;
}

void read_packets(socket_t *socket, packet_list_t *packets)
{
    packet_t *packet = read_socket(socket);

    if (!packet)
        return;
    add_packet(packets, packet);
    socket->mode = WRITE;
}

void add_packet(packet_list_t *packets, packet_t *packet)
{
    packet_node_t *node = NULL;

    strcat(packet->data, CRLF);
    node = create_packet_node(packet);
    if (!node)
        return;
    if (LIST_FIRST(packets))
        LIST_INSERT_AFTER(LIST_FIRST(packets), node, entries);
    else
        LIST_INSERT_HEAD(packets, node, entries);
}
