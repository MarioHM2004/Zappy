/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** map
*/

#ifndef MAP_H_
#define MAP_H_

enum items_e {
    FOOD,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME,
    EGG
};

typedef struct tile_s {
    items_e *item;
} tile_t;

typedef struct map_s {
    uint width;
    uint height;
    tile_t **tiles;
} map_t;

#endif /* !MAP_H_ */
