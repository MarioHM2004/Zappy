/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** client_utils
*/

#include "server/client.h"
#include "libs/log.h"
#include "zappy.h"
#include <stddef.h>

client_t *get_client_by_fd(client_list_t *clients, int fd)
{
    client_node_t *tmp = NULL;

    if (!clients)
        return NULL;
    LIST_FOREACH(tmp, clients, entries) {
        if (tmp->client->socket->fd == fd)
            return tmp->client;
    }
    return NULL;
}

void log_client(client_t *client)
{
    char *type = "PENDING";

    if (!client)
        return;
    if (client->type == GRAPHIC)
        type = "GRAPHIC";
    else if (client->type == AI)
        type = "AI";
    log_info("Client={type=%s}%s", type, LOG_NEXT);
    log_socket(client->socket);
}
