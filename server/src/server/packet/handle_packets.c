/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** packets
*/

#include "server/server.h"
#include "server/socket.h"
#include <sys/select.h>

void handle_packets(server_t *server)
{
    client_node_t *tmp = NULL;

    if (!server->clients)
        return;
    LIST_FOREACH(tmp, server->clients, entries) {
        if (FD_ISSET(tmp->client->socket->fd, &server->write_fds))
            write_packets(tmp->client->socket, &tmp->client->response);
        else if (FD_ISSET(tmp->client->socket->fd, &server->read_fds)) {
            read_packets(tmp->client->socket, tmp->client->request);
            process_client_packets(server, tmp->client);
        }
    }
}
