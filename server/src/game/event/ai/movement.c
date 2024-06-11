/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** movement
*/

// forward, turn_right, turn_left, look

#include "game/game.h"
#include "game/map.h"
#include "game/player.h"
#include "game/resources.h"
#include "libs/log.h"
#include <stdlib.h>

void forward(game_t *game, player_t *player, event_t *event)
{
    position_t new_pos = dir_at(game->map, player->pos, player->dir);

    move_player(game->map, player, new_pos);
    log_debug("Player %d moved to %d %d", player->number, player->pos.x,
        player->pos.y);
}

static direction_e right_dir(direction_e dir)
{
    if (dir < 4)
        dir++;
    else
        dir = 1;
}

void turn_right(game_t *game, player_t *player, event_t *event)
{
    (void)game;
    (void)event;
    if (player->dir < 1 || player->dir > 4)
        return;
    player->dir = right_dir(player->dir);
}

static direction_e left_dir(direction_e dir)
{
    if (dir > 1)
        dir--;
    else
        dir = 4;
}

void turn_left(game_t *game, player_t *player, event_t *event)
{
    (void)game;
    (void)event;
    if (player->dir < 1 || player->dir > 4)
        return;
    player->dir = left_dir(player->dir);
}

static position_t first_position_in_row(game_t *game, direction_e player_dir,
    position_t row_pos, uint tiles_in_row)
{
    direction_e left_direction = left_dir(player_dir);

    for (int i = 0; i < (tiles_in_row / 2); i++) {
        row_pos = dir_at(game->map, row_pos, left_direction);
    }
    return row_pos;
}

static char *get_look_content(resources_t **look_resources)
{
    char *look_content = NULL;

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
    direction_e right_direction = right_dir(player->dir);
    resources_t **look_resources = calloc(1, sizeof(resources_t *) *
        (look_total_tiles(player->level) + 1));
    uint count = 0;
    char *look_content = NULL;

    for (int i = 0; i < player->level; i++) {
        tile_pos = first_position_in_row(game, player->dir,
            row_pos, (i * 2) + 1);
        for (int j = 0; j < (i * 2) + 1; j++) {
            look_resources[count] = map_at(game->map, tile_pos).resource;
            tile_pos = dir_at(game->map, tile_pos, right_direction);
            count++;
        }
        row_pos = dir_at(game->map, row_pos, player->dir);
    }
    look_resources[count] = NULL;
    look_content = get_look_content(look_resources);
}