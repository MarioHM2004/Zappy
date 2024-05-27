/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** tile
*/

#include "game/map.h"
#include <stdlib.h>

tile_t *create_tile(void)
{
    tile_t *tile = calloc(1, sizeof(tile_t));

    if (!tile)
        return NULL;
    tile->resources = create_resources();
    tile->players = 0;
    return tile;
}

void destroy_tile(tile_t *tile)
{
    if (tile->resources)
        destroy_resources(tile->resources);
    if (tile)
        free(tile);
}

tile_t ***create_tiles(uint width, uint height)
{
    tile_t ***tiles = calloc(width, sizeof(tile_t *));

    if (!tiles)
        return NULL;
    for (uint i = 0; i < width; i++) {
        tiles[i] = calloc(height, sizeof(tile_t));
        if (!tiles[i]) {
            destroy_tiles(tiles, width, height);
            return NULL;
        }
        for (uint j = 0; j < height; j++) {
            tiles[i][j] = create_tile();
            if (!tiles[i][j]) {
                destroy_tiles(tiles, width, height);
                return NULL;
            }
        }
    }
    return tiles;
}

void destroy_tiles(tile_t ***tiles, uint width, uint height)
{
    for (uint i = 0; i < width && tiles[i]; i++) {
        for (uint j = 0; j < height && tiles[i][j]; j++) {
            destroy_tile(tiles[i][j]);
        }
        free(tiles[i]);
    }
    free(tiles);
}