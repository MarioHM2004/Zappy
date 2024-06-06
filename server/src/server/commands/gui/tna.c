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

    if (sscanf(cmd, TNA_REQUEST) == -1)
        return packet_message(client, INVALID_PARAMETERS);
    LIST_FOREACH(tmp, server->game->teams, entries) {
        response = safe_strcat(response, formatstr(TNA_RESPONSE, tmp->team->name));
        if (LIST_NEXT(tmp, entries))
            response = safe_strcat(response, CRLF);
    }
    add_response(client, response);
}
