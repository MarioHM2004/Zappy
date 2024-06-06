/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** pgt
*/

#include "libs/lib.h"
#include "server/command.h"
#include "game/player.h"
#include "game/resources.h"

void pgt_command(server_t *server, client_t *client,
    player_t *player, resource_e resource)
{
    packet_t *packet = NULL;

    if (!player)
        return packet_message(client, ERROR_MESSAGE);
    add_response(client, formatstr(PGT_RESPONSE, (int)player->number, resource));
}
