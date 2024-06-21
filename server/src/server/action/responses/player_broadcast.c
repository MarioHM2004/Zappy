/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** player_broadcast
*/

#include "game/player.h"
#include "libs/lib.h"
#include "libs/log.h"
#include "server/client.h"
#include "server/command.h"
#include "server/server.h"
#include "server/action.h"
#include <sys/queue.h>

static void broadcast_receivers(server_t *server, action_t *action)
{
    player_node_t *player_tmp = NULL;
    client_t *client = NULL;
    uint count = 0;

    if (action->data.broadcast.sound_dir == NULL)
        return;
    LIST_FOREACH(player_tmp, server->game->players, entries) {
        if (action->data.broadcast.player == player_tmp->player)
            continue;
        client = get_client_by_fd(server->clients, player_tmp->player->fd);
        if (!client)
            continue;
        add_response(client, formatstr(BROADCAST_RECEIVER,
            action->data.broadcast.sound_dir[count],
                action->data.broadcast.text));
        count++;
    }
}

void player_broadcast(server_t *server, action_t *action)
{
    client_node_t *client_tmp = NULL;
    client_t *client = NULL;

    if (!server || !action)
        return;
    LIST_FOREACH(client_tmp, server->clients, entries) {
        if (client_tmp->client->type != GRAPHIC)
            continue;
        pbc_command(server, client_tmp->client, action->data.broadcast.player,
            action->data.broadcast.text);
    }
    broadcast_receivers(server, action);
    client = get_client_by_fd(server->clients,
        action->data.broadcast.player->fd);
    if (client)
        add_response(client, BROADCAST_SENDER);
    free(action->data.broadcast.sound_dir);
}
