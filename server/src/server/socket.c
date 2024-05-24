/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** socket
*/

#include "server/socket.h"
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

static void set_address(socket_t *socket, int port, in_addr_t addr)
{
    socket->addr.sin_family = AF_INET;
    socket->addr.sin_addr.s_addr = addr;
    socket->addr.sin_port = htons(port);
    socket->addr_len = sizeof(socket->addr);
}

static bool set_socket_options(socket_t *socket)
{
    int opt = -1;

    if (setsockopt(socket->fd, SOL_SOCKET,
        SO_REUSEADDR, &opt, sizeof(int)) < 0)
        return false;
    return true;
}

socket_t *create_socket(int port, in_addr_t addr)
{
    socket_t *s = calloc(1, sizeof(socket_t));

    if (!s)
        return NULL;
    s->fd = socket(AF_INET, SOCK_STREAM, 0);
    s->mode = EXCEPT;
    s->connected = true;
    if (s->fd < 0) {
        free(s);
        return NULL;
    }
    set_address(s, port, addr);
    set_socket_options(s);
    return s;
}

void destroy_socket(socket_t *s)
{
    if (!s)
        return;
    close(s->fd);
    free(s);
}

bool bind_socket(socket_t *s)
{
    if (bind(s->fd, (struct sockaddr *)&s->addr, s->addr_len) < 0)
        return false;
    return true;
}

bool listen_socket(socket_t *s, int backlog)
{
    if (listen(s->fd, backlog) < 0)
        return false;
    if (getsockname(s->fd, (struct sockaddr *)&s->addr, &s->addr_len) < 0)
        return false;
    return true;
}

socket_t *accept_socket(socket_t *s)
{
    socket_t *new_socket = calloc(1, sizeof(socket_t));

    if (!new_socket)
        return NULL;
    new_socket->fd = accept(s->fd, (struct sockaddr *)&new_socket->addr,
        &new_socket->addr_len);
    if (new_socket->fd < 0) {
        free(new_socket);
        return NULL;
    }
    new_socket->mode = EXCEPT;
    new_socket->connected = true;
    return new_socket;
}
