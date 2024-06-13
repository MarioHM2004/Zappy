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

void mct_command(server_t *server, client_t *client, char *cmd)
{
    char *response = "";
    bool last = false;

    if (sscanf(cmd, MCT_REQUEST) == -1)
        return packet_message(client, INVALID_PARAMETERS);
    for (size_t i = 0; i < server->game->map->height; i++) {
        for (size_t j = 0; j < server->game->map->width; j++) {
            last = (i == server->game->map->height - 1 &&
                j == server->game->map->width - 1);
            response = safe_strcat(response, get_tile_content(server, i, j));
            response = safe_strcat(response, (last) ? "" : CRLF);
        }
    }
    add_response(client, response);
    if (response)
        free(response);
}
