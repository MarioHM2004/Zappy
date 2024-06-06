/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** msz
*/

#include "libs/lib.h"
#include "server/command.h"
#include "game/map.h"

void msz_command(server_t *server, client_t *client, char *cmd)
{
    char *response = formatstr(MSZ_RESPONSE,
        (int)server->game->map->width, (int)server->game->map->height);
    packet_t *packet = NULL;

    if (sscanf(cmd, MSZ_REQUEST) == -1)
        return packet_message(client, INVALID_PARAMETERS);
    if (!response)
        return;
    packet = create_packet(response);
    free(response);
    if (!packet)
        return;
    add_packet(client->response, packet);
}