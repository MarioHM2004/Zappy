/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** ppo
*/

#include "libs/lib.h"
#include "server/command.h"
#include "game/player.h"

static char *get_pp(server_t *server, int player)
{
    player_node_t *tmp = NULL;

    if (!server->game->players)
        return NULL;
    LIST_FOREACH(tmp, server->game->players, entries) {
        if ((int)tmp->player->number != player)
            continue;
        return formatstr(PPO_RESPONSE, player,
            (int)tmp->player->pos.x,
            (int)tmp->player->pos.y, (int)tmp->player->dir);
    }
    return NULL;
}

void ppo_command(server_t *server, client_t *client, char *cmd)
{
    int player;
    char *response = NULL;
    packet_t *packet = NULL;
    player_node_t *tmp = NULL;

    if (sscanf(cmd, PPO_REQUEST, &player) == -1)
        return packet_message(client, INVALID_PARAMETERS);
    response = get_pp(server, player);
    if (!response)
        return packet_message(client, ERROR_MESSAGE);
    packet = create_packet(response);
    free(response);
    if (!packet)
        return packet_message(client, ERROR_MESSAGE);
    add_packet(client->response, packet);
}
