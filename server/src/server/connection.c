/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** connection
*/

#include "server/client.h"
#include "server/server.h"
#include "server/socket.h"
#include <sys/queue.h>
#include <sys/select.h>

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
    node = create_client_node(client);
    if (!node)
        return;
    if (LIST_FIRST(server->clients))
        LIST_INSERT_AFTER(LIST_FIRST(server->clients), node, entries);
    else
        LIST_INSERT_HEAD(server->clients, node, entries);
}

static void close_client_connection(client_list_t *clients)
{
    client_node_t *tmp = NULL;

    if (!clients)
        return;
    LIST_FOREACH(tmp, clients, entries) {
        if (tmp->client->socket->connected)
            continue;
        LIST_REMOVE(tmp, entries);
        destroy_client(tmp->client);
    }
}

void close_connection(server_t *server)
{
    close_client_connection(server->clients);
}
