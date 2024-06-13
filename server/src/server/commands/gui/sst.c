/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** sst
*/

#include "server/command.h"
#include "libs/lib.h"

void sst_command(server_t *server, client_t *client, char *cmd)
{
    char *response = NULL;
    int freq = 0;

    if (sscanf(cmd, SST_REQUEST, &freq) == -1)
        return packet_message(client, INVALID_PARAMETERS);
    server->game->freq = freq;
    response = formatstr(SST_REPONSE, freq);
    add_response(client, response);
    if (response)
        free(response);
}
