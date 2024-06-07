/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** smg
*/

#include "libs/lib.h"
#include "server/command.h"
#include "game/player.h"

void smg_command(server_t *server, client_t *client, char *msg)
{
    if (!msg)
        return packet_message(client, ERROR_MESSAGE);
    add_response(client, formatstr(SMG_RESPONSE, msg));
}