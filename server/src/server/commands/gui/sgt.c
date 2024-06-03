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
    char *response = NULL;

    sscanf(cmd, SGT_REQUEST);
    response = formatstr(SGT_RESPONSE, (int)server->game->freq);
    if (!response)
        return packet_error(client);
    add_packet(client->response, create_packet(response));
    free(response);
}
