/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** player_inventory
*/

#include "libs/lib.h"
#include "server/command.h"
#include "server/server.h"
#include "server/action.h"
#include "game/player.h"
#include <sys/queue.h>

void player_inventory(server_t *server, action_t *action)
{
    client_node_t *node = NULL;
    char *command = NULL;

    if (!server || !action)
        return;
    command = formatstr(PIN_REQUEST, action->data.player->number);
    if (!command)
        return;
    LIST_FOREACH(node, server->clients, entries) {
        if (node->client->type != GRAPHIC)
            continue;
        pin_command(server, node->client, command);
    }
    free(command);
}
