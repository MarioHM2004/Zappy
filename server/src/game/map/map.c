/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** map
*/

#include "game/map.h"
#include "game/game.h"
#include "libs/log.h"
#include <stdlib.h>

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
    if (width * height < 7) {
        log_fatal("Map size is too small, it should be at least 3x3\n");
        return NULL;
    }
    map->width = width;
    map->height = height;
    map->tiles = create_tiles(width, height);
    spawn_all_resources(map);
    return map;
}
