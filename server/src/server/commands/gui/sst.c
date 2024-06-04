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
        return packet_error(client);
    server->game->freq = freq;
    response = formatstr(SST_REPONSE, freq);
    if (!response)
        return packet_error(client);
    add_packet(client->response, create_packet(response));
    free(response);
}
