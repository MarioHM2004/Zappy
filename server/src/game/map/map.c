/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** map
*/

#include "game/map.h"
#include <stdlib.h>




tile_t map_at(map_t* map, int x, int y)
{
    if (x < 0)
        x = map->width + (x % map->width);
    else
        x = x % map->width;
    if (y < 0)
        y = map->height + (y % map->height);
    else
        y = y % map->height;

    return map->tiles[y][x];
}

void destroy_map(map_t *map)
{
    for (uint i = 0; i < map->height; i++) {
        free(map->tiles[i]);
    }
    free(map->tiles);
    free(map);
}

map_t *create_map(uint width, uint height)
{
    map_t *map = calloc(1, sizeof(map_t));

    if (!map)
        return NULL;
    map->width = width;
    map->height = height;
    map->tiles = create_tiles(width, height);
    spawn_all_resources(map);
    return map;
}
