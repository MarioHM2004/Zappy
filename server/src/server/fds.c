/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** fds
*/

#include "gui.h"
#include "server.h"

static void clear_fd_sets(fd_set *read_fds, fd_set *write_fds, fd_set *except_fds)
{
    FD_ZERO(read_fds);
    FD_ZERO(write_fds);
    FD_ZERO(except_fds);
}

static void set_client_fds(client_list_t *clients, fd_set *read_fds, fd_set *write_fds, fd_set *except_fds)
{
    client_node_t *tmp = NULL;

    if (!clients)
        return;
    LIST_FOREACH(tmp, clients, entries) {
        if (tmp->client->socket->mode == READ)
            FD_SET(tmp->client->socket->fd, read_fds);
        if (tmp->client->socket->mode == WRITE)
            FD_SET(tmp->client->socket->fd, write_fds);
        if (tmp->client->socket->mode == EXCEPT)
            FD_SET(tmp->client->socket->fd, except_fds);
    }
}

static void set_guis_fds(gui_list_t *guis, fd_set *read_fds, fd_set *write_fds, fd_set *except_fds)
{
    gui_node_t *tmp = NULL;

    if (!guis)
        return;
    LIST_FOREACH(tmp, guis, entries) {
        if (tmp->gui->socket->mode == READ)
            FD_SET(tmp->gui->socket->fd, read_fds);
        if (tmp->gui->socket->mode == WRITE)
            FD_SET(tmp->gui->socket->fd, write_fds);
        if (tmp->gui->socket->mode == EXCEPT)
            FD_SET(tmp->gui->socket->fd, except_fds);
    }
}

static void set_pending_fds(pending_list_t *pendings, fd_set *read_fds, fd_set *write_fds, fd_set *except_fds)
{
    pending_node_t *tmp = NULL;

    if (!pendings)
        return;
    LIST_FOREACH(tmp, pendings, entries) {
        if (tmp->pending->socket->mode == READ)
            FD_SET(tmp->pending->socket->fd, read_fds);
        if (tmp->pending->socket->mode == WRITE)
            FD_SET(tmp->pending->socket->fd, write_fds);
        if (tmp->pending->socket->mode == EXCEPT)
            FD_SET(tmp->pending->socket->fd, except_fds);
    }
}

void set_fds(server_t *server)
{
    clear_fd_sets(&server->read_fds, &server->write_fds, &server->except_fds);
    FD_SET(server->socket->fd, &server->read_fds);
    set_client_fds(server->clients, &server->read_fds,
        &server->write_fds, &server->except_fds);
    set_guis_fds(server->guis, &server->read_fds,
        &server->write_fds, &server->except_fds);
    set_pending_fds(server->pending, &server->read_fds,
        &server->write_fds, &server->except_fds);
}
