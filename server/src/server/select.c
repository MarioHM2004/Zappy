/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** select
*/

#include "server.h"

static int get_biggest_fd(server_t *server)
{
    client_node_t *clients = NULL;
    gui_node_t *guis = NULL;
    pending_node_t *pendings = NULL;
    int biggest = -1;

    biggest = MAX(biggest, server->socket->fd);
    LIST_FOREACH(clients, server->clients, entries)
        biggest = MAX(biggest, clients->client->socket->fd);
    LIST_FOREACH(guis, server->guis, entries)
        biggest = MAX(biggest, guis->gui->socket->fd);
    LIST_FOREACH(pendings, server->pending, entries)
        biggest = MAX(biggest, pendings->pending->socket->fd);
    return biggest;
}

int select_connection(server_t *server)
{
    int biggest_fd = get_biggest_fd(server);
    int activity = 0;

    activity = select(biggest_fd + 1, &server->read_fds, &server->write_fds,
        &server->except_fds, NULL);
    if (activity < 0)
        return -1;
    return activity;
}
