/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** tna
*/

#include "libs/lib.h"
#include "server/command.h"
#include "game/team.h"

void tna_command(server_t *server, client_t *client, char *cmd)
{
    char *response = "";
    team_node_t *tmp = NULL;
    packet_t *packet = NULL;

    if (sscanf(cmd, TNA_REQUEST) == -1)
        return packet_error(client);
    LIST_FOREACH(tmp, server->game->teams, entries) {
        response = safe_strcat(response, formatstr(TNA_RESPONSE, tmp->team->name));
        if (LIST_NEXT(tmp, entries))
            response = safe_strcat(response, CRLF);
    }
    if (!response)
        return packet_error(client);
    packet = create_packet(response);
    if (!packet)
        return packet_error(client);
    add_packet(client->response, packet);
}
