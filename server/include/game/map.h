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

typedef enum {
    N = 1,
    E = 2,
    S = 3,
    W = 4,
    NE = 5,
    SE = 6,
    NW = 7,
    SW = 8
} sound_e;

typedef enum {
    NORTH = 1,
    EAST = 2,
    SOUTH = 3,
    WEST = 4
} direction_e;

typedef struct tile_s {
    resources_t *resource;
    uint players;
    uint eggs;
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
bool change_eggs_tile(map_t *map, position_t pos, int change);
player_list_t *get_players_on_tile(player_list_t *player_list,
    position_t pos, player_state_e state);
void spawn_eggs(map_t *map, game_t *game);

tile_t map_at(map_t* map, position_t pos);
position_t pos_at(map_t *map, position_t pos);
position_t dir_at(map_t *map, position_t pos, direction_e dir);
position_t get_random_pos(map_t *map);
direction_e get_random_dir(void);
direction_e right_dir(direction_e dir);
direction_e left_dir(direction_e dir);

#endif /* !MAP_H_ */
