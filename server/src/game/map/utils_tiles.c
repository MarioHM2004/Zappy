/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** utils_tiles
*/

#include "game/game.h"
#include "game/map.h"
#include "game/resources.h"
#include <sys/types.h>

bool change_resource_tile(map_t *map, position_t pos, resource_e item, uint quantity)
{
    tile_t tile = map_at(map, pos);
    uint *resource = get_resource_ptr(tile.resource, item);

    if (change_resource(tile.resource, item, quantity) == false)
        return false;
    return true;
}

bool change_players_tile(map_t *map, position_t pos, int change)
{
    tile_t tile = map_at(map, pos);

    if (tile.players + change < 0)
        return false;
    tile.players += change;
    update_tile(map, tile, pos);
    return true;
}