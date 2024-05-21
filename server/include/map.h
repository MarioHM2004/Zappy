/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** map
*/

#ifndef MAP_H_
#define MAP_H_

#include <sys/types.h>

enum resource_e {
    FOOD = 1,
    LINEMATE = 2,
    DERAUMERE = 3,
    SIBUR = 4,
    MENDIANE = 5,
    PHIRAS = 6,
    THYSTAME = 7
};

typedef struct resources_s {
    uint food;
    uint linemate;
    uint deraumere;
    uint sibur;
    uint mendiane;
    uint phiras;
    uint thystame;
} resources_t;

typedef struct tile_s {
    resources_t *resources;
    uint players;
} tile_t;

typedef struct map_s {
    uint width;
    uint height;
    tile_t **tiles;
} map_t;

#endif /* !MAP_H_ */
