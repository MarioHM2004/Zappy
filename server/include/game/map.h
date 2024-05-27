/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** map
*/

#ifndef MAP_H_
    #define MAP_H_

    #include <sys/types.h>
    #include "resources.h"

typedef struct position_s {
    uint x;
    uint y;
} position_t;

typedef struct tile_s {
    resources_t *resources;
    uint players;
} tile_t;

typedef struct map_s {
    uint width;
    uint height;
    tile_t ***tiles;
} map_t;

map_t *create_map(uint width, uint height);
void destroy_map(map_t *m);

tile_t ***create_tiles(uint width, uint height);
void destroy_tiles(tile_t ***tiles, uint width, uint height);
tile_t *create_tile(void);
void destroy_tile(tile_t *t);

resources_t *create_resources(void);
void destroy_resources(resources_t *rs);

#endif /* !MAP_H_ */
