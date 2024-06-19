/*
** EPITECH PROJECT, 2024
** responses
** File description:
** egg_matured
*/

#include "server/client.h"
#include "server/command.h"
#include "server/server.h"
#include "server/action.h"
#include <sys/queue.h>

void egg_matured(server_t *server, action_t *action)
{
    client_node_t *node = NULL;

    if (!server || !action)
        return;
    LIST_FOREACH(node, server->clients, entries) {
        if (node->client->type != GRAPHIC)
            continue;
        eht_command(server, node->client, action->data.player);
    }
}

