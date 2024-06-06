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
    packet_t *packet = NULL;
    char *response = NULL;

    if (!player || !egg)
        return packet_message(client, ERROR_MESSAGE);
    response = formatstr(ENW_RESPONSE, (int)egg->number,
        player->number, egg->pos.x, egg->pos.y);
    if (!response)
        return packet_message(client, ERROR_MESSAGE);
    packet = create_packet(response);
    free(response);
    if (!packet)
        return packet_message(client, ERROR_MESSAGE);
    add_packet(client->response, packet);
}
