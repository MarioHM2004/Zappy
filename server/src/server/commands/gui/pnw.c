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

void pnw_command(server_t *server, client_t *client, player_t *player)
{
    char *response = formatstr(PNW_RESPONSE,
        (int)player->number, (int)player->pos.x,
        (int)player->pos.y, (int)player->dir,
        (int)player->level,
        get_team_by_player(server->game, player));

    if (!player || !response)
        return packet_message(client, ERROR_MESSAGE);
    add_response(client, response);
    free(response);
}
