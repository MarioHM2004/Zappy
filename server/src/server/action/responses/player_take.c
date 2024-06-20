/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** player_take
*/

#include "server/command.h"
#include "server/server.h"
#include "server/action.h"
#include <sys/queue.h>

action_t *create_player_take_action(player_t *player, resource_e resource)
{
    object_t object = {
        .player = player,
        .resource = resource
    };
    action_t *action = create_action(PLAYER_TAKE, &object, sizeof(object_t));

    return action;
}

void player_take(server_t *server, action_t *action)
{
    client_node_t *node = NULL;

    if (!server || !action)
        return;
    LIST_FOREACH(node, server->clients, entries) {
        if (node->client->type != GRAPHIC)
            continue;
        pgt_command(server, node->client, action->data.object.player, action->data.object.resource);
    }
}
