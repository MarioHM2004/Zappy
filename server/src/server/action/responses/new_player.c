/*
** EPITECH PROJECT, 2024
** responses
** File description:
** new_player
*/

#include "game/player.h"
#include "libs/lib.h"
#include "libs/log.h"
#include "server/command.h"
#include "server/server.h"
#include "server/action.h"

static void send_guis_player_info(server_t *server, player_t *player)
{
    client_node_t *node = NULL;
    char *command = NULL;

    if (!player)
        return;
    command = formatstr("pin %d", player->number);
    LIST_FOREACH(node, server->clients, entries) {
        if (node->client->type != GRAPHIC)
            continue;
        pnw_command(server, node->client, player);
        pin_command(server, node->client, command);
        ebo_command(server, node->client, player);
        node->client->socket->mode = WRITE;
    }
    free(command);
}

void new_player(server_t *server, action_t *action)
{
    player_t *player = NULL;

    if (!server || !action)
        return;
    player = get_player_by_fd(server->game->players,
        action->data.client->socket->fd);
    log_debug("Pos x: %d, y: %d", player->pos.x, player->pos.y);
    if (!player)
        return;
    pnw_command(server, action->data.client, player);
    msz_command(server, action->data.client, "msz");
    send_guis_player_info(server, player);
}

