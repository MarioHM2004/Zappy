/*
** EPITECH PROJECT, 2024
** responses
** File description:
** egg_matured
*/

#include "game/player.h"
#include "server/client.h"
#include "server/command.h"
#include "server/server.h"
#include "server/action.h"
#include <stdlib.h>
#include <sys/queue.h>

action_t *create_egg_matured_action(player_t *player)
{
    action_t *action = create_action(EGG_MATURED, player, sizeof(player_t));

    return action;
}

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

