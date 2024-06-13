/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** connection
*/

#include "server/client.h"
#include "server/packet.h"
#include "server/server.h"
#include "server/socket.h"
#include <sys/queue.h>
#include <sys/select.h>

static void welcome_message(client_t *client)
{
    packet_t *packet = create_packet("WELCOME" CRLF);
    packet_node_t *node = NULL;

    if (!packet)
        return;
    node = create_packet_node(packet);
    if (!node)
        return;
    LIST_INSERT_HEAD(client->response, node, entries);
    client->socket->mode = WRITE;
}

static void add_client(client_list_t *clients, client_node_t *node)
{
    log_socket(node->client->socket);
    if (LIST_FIRST(clients))
        LIST_INSERT_AFTER(LIST_FIRST(clients), node, entries);
    else
        LIST_INSERT_HEAD(clients, node, entries);
}

void accept_connection(server_t *server)
{
    socket_t *socket = NULL;
    client_t *client = NULL;
    client_node_t *node = NULL;

    if (!FD_ISSET(server->socket->fd, &server->read_fds))
        return;
    socket = accept_socket(server->socket);
    if (!socket)
        return;
    client = create_client(socket);
    if (!client)
        return;
    welcome_message(client);
    node = create_client_node(client);
    if (!node)
        return;
    add_client(server->clients, node);
}

void close_connection(server_t *server)
{
    client_node_t *tmp = NULL;

    if (!server)
        return;
    LIST_FOREACH(tmp, server->clients, entries) {
        if (!FD_ISSET(tmp->client->socket->fd, &server->except_fds)
            && tmp->client->socket->mode != EXCEPT)
            continue;
        LIST_REMOVE(tmp, entries);
        destroy_client(tmp->client);
    }
}
