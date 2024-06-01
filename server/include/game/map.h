/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** map
*/

#ifndef MAP_H_
    #define MAP_H_

    #include "game/game.h"
    #include "resources.h"

    #include <sys/types.h>

typedef struct tile_s {
    resources_t *resource;
    uint players;
} tile_t;

typedef struct map_s {
    uint width;
    uint height;
    tile_t **tiles;
} map_t;

map_t *create_map(uint width, uint height);
void destroy_map(map_t *m);

tile_t **create_tiles(uint width, uint height);
void destroy_tiles(tile_t **tiles, uint width, uint height);
tile_t create_tile(void);

bool update_tile(map_t *map, tile_t new_tile, position_t pos);
bool change_resource_tile(map_t *map, position_t pos, resource_e item, uint quantity);
bool change_players_tile(map_t *map, position_t pos, int change);

tile_t map_at(map_t* map, position_t pos);
position_t pos_at(map_t *map, position_t pos);

#endif /* !MAP_H_ */
