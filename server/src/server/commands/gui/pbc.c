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
    char *response = formatstr(PBC_RESPONSE, (int)player->number, msg);

    if (!player || !msg || !response)
        return packet_message(client, ERROR_MESSAGE);
    add_response(client, response);
    free(response);
}
