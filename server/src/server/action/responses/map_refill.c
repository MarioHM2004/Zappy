/*
** EPITECH PROJECT, 2024
** responses
** File description:
** map_refill
*/

#include "server/client.h"
#include "server/command.h"
#include "server/server.h"
#include "server/action.h"
#include <sys/queue.h>

void map_refill(server_t *server, action_t *action)
{
    client_node_t *node = NULL;

    if (!server || !action)
        return;
    LIST_FOREACH(node, server->clients, entries) {
        if (node->client->type != GRAPHIC)
            continue;
        mct_command(server, node->client, "mct");
    }
}

