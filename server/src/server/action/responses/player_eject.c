/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** player_eject
*/

#include "game/game.h"
#include "game/player.h"
#include "libs/lib.h"
#include "server/command.h"
#include "server/server.h"
#include "server/action.h"
#include <sys/queue.h>

static void eject_receivers(server_t *server, action_t *action)
{
    player_node_t *player_tmp = NULL;
    client_t *client = NULL;
    uint count = 0;

    LIST_FOREACH(player_tmp, action->data.eject.players, entries) {
        client = get_client_by_fd(server->clients, player_tmp->player->fd);
        if (!client)
            continue;
        add_response(client, formatstr(EJECTED_RESPONSE,
            action->data.eject.eject_dir[count]));
        count++;
    }

}

void player_eject(server_t *server, action_t *action)
{
    client_node_t *node = NULL;
    client_t *client = NULL;

    if (!server || !action)
        return;
    LIST_FOREACH(node, server->clients, entries) {
        if (node->client->type != GRAPHIC)
            continue;
        pex_command(server, node->client, action->data.player);
    }
    eject_receivers(server, action);
    client = get_client_by_fd(server->clients,
        action->data.eject.player->fd);
    if (client)
        add_response(client, EJECT_RESPONSE);
}
