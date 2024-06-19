/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** player_dead
*/

#include "server/command.h"
#include "server/server.h"
#include "server/action.h"
#include <sys/queue.h>

void player_dead(server_t *server, action_t *action)
{
    client_node_t *node = NULL;

    if (!server || !action)
        return;
    LIST_FOREACH(node, server->clients, entries) {
        if (node->client->type != GRAPHIC)
            continue;
        pdi_command(server, node->client, action->data.player);
    }
}
