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

char *get_tile_content(server_t *server, int width, int height)
{
    char *res = formatstr(BCT_RESPONSE, width, height,
        (int)server->game->map->tiles[width][height]->resource->food,
        (int)server->game->map->tiles[width][height]->resource->linemate,
        (int)server->game->map->tiles[width][height]->resource->deraumere,
        (int)server->game->map->tiles[width][height]->resource->sibur,
        (int)server->game->map->tiles[width][height]->resource->mendiane,
        (int)server->game->map->tiles[width][height]->resource->phiras,
        (int)server->game->map->tiles[width][height]->resource->thystame,
    );
    return res;
}

void bct_command(server_t *server, client_t *client, char *cmd)
{
    int width;
    int height;
    char *response;
    packet_t *packet = NULL;

    scanf(BCT_REQUEST, &width, &height);
    if (server->game->map->width >= width || server->game->map->height >= height)
        return packet_error(client);
    response = get_tile_content(server, width, height);
    packet = create_packet(response);
}