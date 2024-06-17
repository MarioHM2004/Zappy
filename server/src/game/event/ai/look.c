/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** look
*/



#include "game/game.h"
#include "game/map.h"
#include "game/player.h"
#include "game/resources.h"
#include "game/event.h"
#include "libs/lib.h"
#include "libs/log.h"
#include "server/server.h"
#include <time.h>

static position_t first_position_in_row(game_t *game, direction_e player_dir,
    position_t row_pos, uint tiles_in_row)
{
    direction_e left_direction = left_dir(player_dir);

    row_pos = dir_at(game->map, row_pos, player_dir);
    for (int i = 0; i < (tiles_in_row / 2); i++) {
        row_pos = dir_at(game->map, row_pos, left_direction);
    }
    return row_pos;
}

static char *format_item_name(char *item_name, char *new_item_name)
{
    if (item_name == NULL)
        return new_item_name;
    else
        return formatstr("%s %s", item_name, new_item_name);
}

static char *get_item_name(tile_t look_tiles)
{
    char *item_name = NULL;

    if (look_tiles.resource == NULL)
        return item_name;
    if (look_tiles.resource->food > 0)
        item_name = format_item_name(item_name, "food");
    if (look_tiles.resource->linemate > 0)
        item_name = format_item_name(item_name, "linemate");
    if (look_tiles.resource->deraumere > 0)
        item_name = format_item_name(item_name, "deraumere");
    if (look_tiles.resource->sibur > 0)
        item_name = format_item_name(item_name, "sibur");
    if (look_tiles.resource->mendiane > 0)
        item_name = format_item_name(item_name, "mendiane");
    if (look_tiles.resource->phiras > 0)
        item_name = format_item_name(item_name, "phiras");
    if (look_tiles.resource->thystame > 0)
        item_name = format_item_name(item_name, "thystame");
    if (look_tiles.players > 0)
        item_name = format_item_name(item_name, "player");
    if (look_tiles.eggs > 0)
        item_name = format_item_name(item_name, "egg");
    return item_name;
}
static char *get_look_content(tile_t *look_tiles, uint total_tiles)
{
    char *look_content = NULL;
    char *tile_content = NULL;
    for (int i = 0; i < total_tiles; i++) {
        tile_content = get_item_name(look_tiles[i]);
        if (look_content == NULL)
            look_content = formatstr("%s", tile_content ? tile_content : "");
        else
            look_content = formatstr("%s,%s", look_content,
                tile_content ? tile_content : "");
    }
    log_debug("Look content: %s", look_content);
    return look_content;
}

static uint look_total_tiles(uint level)
{
    uint total_tiles = 1;

    for (int i = 1; i <= level; i++) {
        total_tiles += (i * 2) + 1;
    }
    return total_tiles;
}

void look(game_t *game, player_t *player, event_t *event)
{
    position_t row_pos = player->pos;
    position_t tile_pos = {0};
    uint total_tiles = look_total_tiles(player->level);
    direction_e right_direction = right_dir(player->dir);
    tile_t *look_tiles = calloc(1, sizeof(tile_t) * total_tiles);
    uint count = 1;

    log_debug("Player %d looked", player->number);
    look_tiles[0] = map_at(game->map, player->pos);
    for (int i = 1; i <= player->level; i++) {
        tile_pos = first_position_in_row(game, player->dir,
            row_pos, (i * 2) + 1);
        for (int j = 0; j < (i * 2) + 1; j++) {
            look_tiles[count] = map_at(game->map, tile_pos);
            tile_pos = dir_at(game->map, tile_pos, right_direction);
            count++;
        }
        row_pos = dir_at(game->map, row_pos, player->dir);
    }
    add_response_to_player(game->server->clients, player,
        get_look_content(look_tiles, total_tiles));
}