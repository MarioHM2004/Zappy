/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** utils_tiles
*/

#include "game/game.h"
#include "game/map.h"
#include "game/player.h"

player_list_t *get_players_on_tile(player_list_t *player_list,
    position_t pos, player_state_e state)
{
    player_list_t *players_on_tile = create_player_list();
    player_node_t *tmp = LIST_FIRST(player_list);

    if (!tmp || !players_on_tile)
        return players_on_tile;
    while (tmp) {
        if (tmp->player->pos.x == pos.x && tmp->player->pos.y == pos.y
        && (tmp->player->state == state || state == -1))
            add_player(players_on_tile, tmp->player);
        tmp = LIST_NEXT(tmp, entries);
    }
    return players_on_tile;
}

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

bool change_eggs_tile(map_t *map, position_t pos, int change)
{
    tile_t tile = map_at(map, pos);

    if (tile.players + change < 0)
        return false;
    tile.eggs += change;
    update_tile(map, tile, pos);
    return true;
}