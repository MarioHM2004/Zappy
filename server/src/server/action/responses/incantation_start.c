/*
** EPITECH PROJECT, 2024
** responses
** File description:
** incantation_start
*/

#include "server/command.h"
#include "server/server.h"
#include "server/action.h"
#include <stdlib.h>
#include <sys/queue.h>

void incantation_start(server_t *server, action_t *action)
{
    client_node_t *node = NULL;

    if (!server || !action)
        return;
    LIST_FOREACH(node, server->clients, entries) {
        if (node->client->type != GRAPHIC)
            continue;
        pic_command(server, node->client, action->data.incantation.players);
    }
}
