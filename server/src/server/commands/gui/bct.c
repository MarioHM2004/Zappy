/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** bct
*/

#include "libs/lib.h"
#include "server/command.h"
#include "game/map.h"
#include "game/resources.h"
#include "server/packet.h"

char *get_tile_content(server_t *server, int width, int height)
{
    return formatstr(BCT_RESPONSE, width, height,
        (int)server->game->map->tiles[width][height].resource->food,
        (int)server->game->map->tiles[width][height].resource->linemate,
        (int)server->game->map->tiles[width][height].resource->deraumere,
        (int)server->game->map->tiles[width][height].resource->sibur,
        (int)server->game->map->tiles[width][height].resource->mendiane,
        (int)server->game->map->tiles[width][height].resource->phiras,
        (int)server->game->map->tiles[width][height].resource->thystame
    );
}

void bct_command(server_t *server, client_t *client, char *cmd)
{
    int width;
    int height;
    char *response = NULL;
    packet_t *packet = NULL;

    if (sscanf(cmd, BCT_REQUEST, &width, &height) == -1)
        return packet_message(client, INVALID_PARAMETERS);
    if (width >= server->game->map->width || height >= server->game->map->height)
        return packet_message(client, INVALID_PARAMETERS);
    response = get_tile_content(server, width, height);
    if (!response)
        return packet_message(client, ERROR_MESSAGE);
    packet = create_packet(response);
    if (!packet)
        return packet_message(client, ERROR_MESSAGE);
    add_packet(client->response, packet);
}