/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** ebo
*/

#include "libs/lib.h"
#include "server/command.h"
#include "game/player.h"

void ebo_command(server_t *server, client_t *client, player_t *player)
{
    packet_t *packet = NULL;

    if (!player)
        return packet_message(client, ERROR_MESSAGE);
    add_response(client, formatstr(EBO_RESPONSE, (int)player->number));
}
