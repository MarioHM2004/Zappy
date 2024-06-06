/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** plv
*/

#include "libs/lib.h"
#include "server/command.h"
#include "game/player.h"

static char *get_plv(server_t *server, int player)
{
    player_node_t *tmp = NULL;

    if (!server->game->players)
        return NULL;
    LIST_FOREACH(tmp, server->game->players, entries) {
        if ((int)tmp->player->number != player)
            continue;
        return formatstr(PLV_RESPONSE, player, (int)tmp->player->level);
    }
    return NULL;
}

void plv_command(server_t *server, client_t *client, char *cmd)
{
    int player = 0;

    if (sscanf(cmd, PLV_REQUEST, &player) == -1)
        return packet_message(client, INVALID_PARAMETERS);
    add_response(client, get_plv(server, player));
}
