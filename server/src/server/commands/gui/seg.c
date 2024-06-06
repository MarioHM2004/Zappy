/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** seg
*/

#include "libs/lib.h"
#include "server/command.h"
#include "game/team.h"

void seg_command(server_t *server, client_t *client)
{
    team_node_t *last_team = NULL;
    char *response = NULL;
    packet_t *packet = NULL;

    if (!server->game->ended || LIST_EMPTY(server->game->teams))
        return packet_message(client, ERROR_MESSAGE);;
    last_team = LIST_FIRST(server->game->teams);
    response = formatstr(SEG_RESPONSE, last_team->team->name);
    if (!response)
        return packet_message(client, ERROR_MESSAGE);
    packet = create_packet(response);
    free(response);
    if (!packet)
        return packet_message(client, ERROR_MESSAGE);
    add_packet(client->response, packet);
}
