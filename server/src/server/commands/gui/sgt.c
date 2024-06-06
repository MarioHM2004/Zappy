/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** sgt
*/

#include "libs/lib.h"
#include "server/command.h"

void sgt_command(server_t *server, client_t *client, char *cmd)
{
    if (sscanf(cmd, SGT_REQUEST) == -1)
        return packet_message(client, INVALID_PARAMETERS);
    add_response(client, formatstr(SGT_RESPONSE, (int)server->game->freq));
}
