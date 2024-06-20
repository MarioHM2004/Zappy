/*
** EPITECH PROJECT, 2024
** responses
** File description:
** player_moved
*/

#include "libs/lib.h"
#include "server/command.h"
#include "server/server.h"
#include "server/action.h"
#include <sys/queue.h>

action_t *create_player_moved_action(player_t *player)
{
    action_t *action = create_action(PLAYER_MOVED, player, sizeof(player_t));

    return action;
}

void player_moved(server_t *server, action_t *action)
{
    client_node_t *node = NULL;
    char *command = NULL;

    if (!server || !action)
        return;
    command = formatstr(PPO_REQUEST, action->data.player->number);
    if (!command)
        return;
    LIST_FOREACH(node, server->clients, entries) {
        if (node->client->type != GRAPHIC)
            continue;
        ppo_command(server, node->client, command);
    }
    free(command);
}

