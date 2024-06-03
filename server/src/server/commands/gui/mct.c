/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** mct
*/

#include "libs/lib.h"
#include "server/command.h"
#include "game/map.h"
#include "game/resources.h"
#include "server/packet.h"
#include <string.h>

void mct_command(server_t *server, client_t *client, char *cmd)
{
    char *response = "";
    packet_t *packet = NULL;

    sscanf(cmd, MCT_REQUEST);
    for (size_t i = 0; i < server->game->map->height; i++) {
        for (size_t j = 0; j < server->game->map->width; j++) {
            response = safe_strcat(response, get_tile_content(server, i, j));
            response = safe_strcat(response, CRLF);
        }
    }
    if (!response)
        return packet_error(client);
    packet = create_packet(response);
    if (!packet)
        return packet_error(client);
    add_packet(client->response, packet);
}