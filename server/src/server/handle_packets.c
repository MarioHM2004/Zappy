/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** packets
*/

#include "server/server.h"

static void handle_client_packets(server_t *server)
{
    client_node_t *tmp = NULL;

    if (!server->clients)
        return;
    LIST_FOREACH(tmp, server->clients, entries) {
        if (FD_ISSET(tmp->socket->fd, &server->write_fds))
            write_packets(&tmp->client->response);
        if (FD_ISSET(tmp->socket->fd, &server->read_fds))
            process_client_packets(tmp->client);
    }
    return;
}

static void handle_gui_packets(server_t *server)
{
    gui_node_t *tmp = NULL;

    if (!server->guis)
        return;
    LIST_FOREACH(tmp, server->guis, entries) {
        if (FD_ISSET(tmp->socket->fd, &server->write_fds))
            write_packets(tmp->gui->response);
        if (FD_ISSET(tmp->socket->fd, &server->read_fds))
            process_gui_packets(tmp->gui);
    }
    return;
}

static void handle_pending_packets(server_t *server)
{
    pending_node_t *tmp = NULL;

    if (!server->pending)
        return;
    LIST_FOREACH(tmp, server->pending, entries) {
        if (FD_ISSET(tmp->socket->fd, &server->write_fds))
            write_packets(tmp->pending->response);
        if (FD_ISSET(tmp->socket->fd, &server->read_fds))
            process_pendings_packets(tmp->pending);
    }
    return;
}

void handle_packets(server_t *server)
{
    handle_pending_packets(server);
}
