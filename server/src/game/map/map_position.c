/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** map_position
*/

#include "game/game.h"
#include "game/map.h"
#include <stdlib.h>

position_t dir_at(map_t *map, position_t pos, direction_e dir)
{
    position_t new_pos = {pos.x, pos.y};

    switch (dir) {
        case NORTH:
            new_pos.y--;
            break;
        case EAST:
            new_pos.x++;
            break;
        case SOUTH:
            new_pos.y++;
            break;
        case WEST:
            new_pos.x--;
            break;
    }
    return pos_at(map, new_pos);
}

position_t pos_at(map_t *map, position_t pos)
{

    if (pos.x < 0)
        pos.x = (map->width + pos.x) % map->width;
    else
        pos.x = pos.x % map->width;
    if (pos.y < 0) {
        pos.y = (map->height + pos.y) % map->height;
    }
    else
        pos.y = pos.y % map->height;
    return pos;
}


tile_t map_at(map_t* map, position_t pos)
{
    position_t new_pos = pos_at(map, pos);

    return map->tiles[new_pos.y][new_pos.x];
}

position_t get_random_pos(map_t *map)
{
    position_t pos = {0};

    pos.x = rand() % map->width;
    pos.y = rand() % map->height;
    return pos;
}

direction_e get_random_dir(void)
{
    direction_e dir = rand() % 4;

    return dir + 1;
}
