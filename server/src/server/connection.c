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
    pending_t *pending = NULL;
    pending_node_t *node = NULL;

    if (!FD_ISSET(server->socket->fd, &server->read_fds))
        return;
    socket = accept_socket(server->socket);
    if (!socket)
        return;
    pending = create_pending(socket);
    if (!pending)
        return;
    node = create_pending_node(pending);
    if (!node)
        return;
    if (LIST_FIRST(server->pending))
        LIST_INSERT_AFTER(LIST_FIRST(server->pending), node, entries);
    else
        LIST_INSERT_HEAD(server->pending, node, entries);
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

static void close_gui_connection(gui_list_t *guis)
{
    gui_node_t *tmp = NULL;

    if (!guis)
        return;
    LIST_FOREACH(tmp, guis, entries) {
        if (tmp->gui->socket->connected)
            continue;
        LIST_REMOVE(tmp, entries);
        destroy_gui(tmp->gui);
    }
}

static void close_pending_connection(pending_list_t *pending)
{
    pending_node_t *tmp = NULL;

    if (!pending)
        return;
    LIST_FOREACH(tmp, pending, entries) {
        if (tmp->pending->socket->connected)
            continue;
        LIST_REMOVE(tmp, entries);
        destroy_pending_node(tmp);
    }
}

void close_connection(server_t *server)
{
    close_client_connection(server->clients);
    close_gui_connection(server->guis);
    close_pending_connection(server->pending);
}
