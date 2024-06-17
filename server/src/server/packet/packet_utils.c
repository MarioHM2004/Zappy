/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** send_packets
*/

#include "server/packet.h"
#include "libs/lib.h"
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

bool read_packets(socket_t *socket, packet_list_t *packets)
{
    packet_t *packet = read_socket(socket);

    if (!packet)
        return false;
    add_packet(packets, packet);
    socket->mode = WRITE;
    return true;
}

static void insert_tail(packet_list_t *packets, packet_node_t *node)
{
    packet_node_t *tmp = NULL;

    if (!LIST_FIRST(packets)) {
        LIST_INSERT_HEAD(packets, node, entries);
        return;
    }
    tmp = LIST_FIRST(packets);
    while (LIST_NEXT(tmp, entries))
        tmp = LIST_NEXT(tmp, entries);
    LIST_INSERT_AFTER(tmp, node, entries);
}

void add_packet(packet_list_t *packets, packet_t *packet)
{
    packet_node_t *node = NULL;

    packet->data = safe_strcat(packet->data, CRLF);
    node = create_packet_node(packet);
    if (!node)
        return;
    insert_tail(packets, node);
}

void add_packet_by_fd(server_t *server, int fd, packet_t *packet)
{
    client_t *client = get_client_by_fd(server->clients, fd);

    if (!client)
        return;
    add_packet(client->response, packet);
}

