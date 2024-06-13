/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** pdi
*/

#include "libs/lib.h"
#include "server/command.h"
#include "game/player.h"

void pdi_command(server_t *server, client_t *client, player_t *player)
{
    char *response = formatstr(PDI_RESPONSE, (int)player->number);

    if (!player || !response)
        return packet_message(client, ERROR_MESSAGE);
    add_response(client, response);
    free(response);
}
