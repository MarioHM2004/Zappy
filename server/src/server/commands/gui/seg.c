/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** seg
*/

#include "libs/lib.h"
#include "server/command.h"
#include "game/team.h"

void seg_command(server_t *server, client_t *client, team_t *team)
{
    if (!server->game->ended || !team)
        return packet_message(client, ERROR_MESSAGE);;
    add_response(client, formatstr(SEG_RESPONSE, team->name));
}
