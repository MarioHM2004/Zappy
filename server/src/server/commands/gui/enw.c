/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** enw
*/

#include "libs/lib.h"
#include "server/command.h"
#include "game/player.h"

void enw_command(server_t *server, client_t *client, player_t *player,
    player_t *egg)
{
    if (!player || !egg)
        return packet_message(client, ERROR_MESSAGE);
    add_response(client, formatstr(ENW_RESPONSE, (int)egg->number,
        player->number, egg->pos.x, egg->pos.y));
}
