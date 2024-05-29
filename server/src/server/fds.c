/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** fds
*/

#include "server/server.h"
#include <sys/queue.h>

void set_fds(server_t *server)
{
    client_node_t *tmp = NULL;

    FD_ZERO(&server->read_fds);
    FD_ZERO(&server->write_fds);
    FD_ZERO(&server->except_fds);
    FD_SET(server->socket->fd, &server->read_fds);
    LIST_FOREACH(tmp, server->clients, entries) {
        if (tmp->client->socket->mode == READ)
            FD_SET(tmp->client->socket->fd, &server->read_fds);
        if (tmp->client->socket->mode == WRITE)
            FD_SET(tmp->client->socket->fd, &server->write_fds);
        if (tmp->client->socket->mode == EXCEPT)
            FD_SET(tmp->client->socket->fd, &server->except_fds);
    }
}
