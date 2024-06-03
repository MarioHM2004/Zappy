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

    LIST_FOREACH(tmp, server->game->players, entries) {
        if ((int)tmp->player->number != player)
            continue;
        return formatstr(PLV_RESPONSE, player, (int)tmp->player->level);
    }
    return NULL;
}

void plv_command(server_t *server, client_t *client, char *cmd)
{
    int player;
    char *response = NULL;
    packet_t *packet = NULL;
    player_node_t *tmp = NULL;

    sscanf(cmd, PLV_REQUEST, &player);
    if (!player || !server->game->players)
        return packet_error(client);
    response = get_plv(server, player);
    if (!response)
        return packet_error(client);
    packet = create_packet(response);
    free(response);
    if (!packet)
        return packet_error(client);
    add_packet(client->response, packet);
}
