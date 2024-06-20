/*
** EPITECH PROJECT, 2024
** responses
** File description:
** incantation_end
*/

#include "server/client.h"
#include "server/command.h"
#include "server/server.h"
#include "server/action.h"
#include <stdlib.h>
#include <sys/queue.h>

void incantation_end(server_t *server, action_t *action)
{
    client_node_t *client_node = NULL;
    player_node_t *player_node = NULL;

    if (!server || !action)
        return;
    LIST_FOREACH(client_node, server->clients, entries) {
        if (client_node->client->type != GRAPHIC)
            continue;
        LIST_FOREACH(player_node, action->data.incantation.players, entries) {
            pie_command(server, client_node->client,
                player_node->player,
                action->data.incantation.state == SUCCESSFUL);
        }
    }
}

