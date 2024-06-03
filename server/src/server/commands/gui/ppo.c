/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** ppo
*/

#include "libs/lib.h"
#include "server/command.h"
#include "game/map.h"
#include "game/team.h"

void ppo_command(server_t *server, client_t *client, char *cmd)
{
    char *response = NULL;
    int player;
    packet_t *packet = NULL;
    player_node_t *tmp = NULL;

    sscanf(cmd, PPO_REQUEST, &player);
    if (!player || !server->game->players)
        return packet_error(client);
    LIST_FOREACH(tmp, server->game->players, entries) {
        if ((int)tmp->player->number == player) {
            response = formatstr(PPO_RESPONSE, player,
                (int)tmp->player->pos.x,
                (int)tmp->player->pos.y, (int)tmp->player->dir);
            break;
        }
    }
    if (!response)
        return packet_error(client);
    packet = create_packet(response);
    free(response);
    if (!packet)
        return packet_error(client);
    add_packet(client->response, packet);
}
