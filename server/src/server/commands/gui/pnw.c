/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** pnw
*/

#include "libs/lib.h"
#include "server/command.h"
#include "game/player.h"
#include "game/team.h"

static player_t *get_player_by_number(player_list_t *players, uint player_num)
{
    player_node_t *tmp = NULL;

    LIST_FOREACH(tmp, players, entries) {
        if (tmp->player->number == player_num)
            return tmp->player;
    }
    return NULL;
}

void pnw_command(server_t *server, client_t *client, uint player_num)
{
    packet_t *packet = NULL;
    char *response = NULL;
    player_t *player = get_player_by_number(server->game->players, player_num);

    response = safe_strcat(response, formatstr(PNW_RESPONSE,
        (int)player_num, (int)player->pos.x,
        (int)player->pos.y, (int)player->dir,
        (int)player->level,
        get_team_by_player(server->game, player)));
    if (!response)
        return packet_message(client, ERROR_MESSAGE);
    packet = create_packet(response);
    free(response);
    if (!packet)
        return packet_message(client, ERROR_MESSAGE);
    add_packet(client->response, packet);
}