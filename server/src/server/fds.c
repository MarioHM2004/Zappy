/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** fds
*/

#include "server/pending.h"
#include "server/gui.h"
#include "server/server.h"
#include <sys/queue.h>

static void clear_fd_sets(fd_set *read_fds, fd_set *write_fds, fd_set *except_fds)
{
    FD_ZERO(read_fds);
    FD_ZERO(write_fds);
    FD_ZERO(except_fds);
}

static void set_socket_fd(socket_t *socket, fd_set *read_fds, fd_set *write_fds, fd_set *except_fds)
{
    if (socket->mode == READ)
        FD_SET(socket->fd, read_fds);
    if (socket->mode == WRITE)
        FD_SET(socket->fd, write_fds);
    if (socket->mode == EXCEPT)
        FD_SET(socket->fd, except_fds);
}

void set_fds(server_t *server)
{
    client_node_t *client = NULL;
    gui_node_t *gui = NULL;
    pending_node_t *pending = NULL;

    clear_fd_sets(&server->read_fds, &server->write_fds, &server->except_fds);
    FD_SET(server->socket->fd, &server->read_fds);
    LIST_FOREACH(client, server->pending, entries) {
        set_socket_fd(client->client->socket, &server->read_fds,
            &server->write_fds, &server->except_fds);
    }
    LIST_FOREACH(gui, server->guis, entries) {
        set_socket_fd(gui->gui->socket, &server->read_fds,
            &server->write_fds, &server->except_fds);
    }
    LIST_FOREACH(pending, server->pending, entries) {
        set_socket_fd(pending->pending->socket, &server->read_fds,
            &server->write_fds, &server->except_fds);
    }
}
