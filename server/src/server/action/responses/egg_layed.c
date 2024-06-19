/*
** EPITECH PROJECT, 2024
** responses
** File description:
** egg_layed
*/

#include "server/client.h"
#include "server/command.h"
#include "server/server.h"
#include "server/action.h"
#include <sys/queue.h>

void egg_layed(server_t *server, action_t *action)
{
    client_node_t *node = NULL;

    if (!server || !action)
        return;
    LIST_FOREACH(node, server->clients, entries) {
        if (node->client->type != GRAPHIC)
            continue;
        enw_command(server, node->client,
            action->data.egg_shell.player, action->data.egg_shell.egg);
    }
}

