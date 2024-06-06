/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** pbc
*/

#include "libs/lib.h"
#include "server/command.h"
#include "game/player.h"

void pbc_command(server_t *server, client_t *client,
    player_t *player, char *msg)
{
    packet_t *packet = NULL;
    char *response = NULL;

    if (!player || !msg)
        return packet_message(client, ERROR_MESSAGE);
    response = formatstr(PBC_RESPONSE, (int)player->number, msg);
    if (!response)
        return packet_message(client, ERROR_MESSAGE);
    packet = create_packet(response);
    free(response);
    if (!packet)
        return packet_message(client, ERROR_MESSAGE);
    add_packet(client->response, packet);
}
