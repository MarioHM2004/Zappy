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
#include "libs/log.h"

static position_t dir_at(map_t *map, position_t pos, direction_e dir)
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

void forward(game_t *game, player_t *player, event_t *event)
{
    change_players_tile(game->map, player->pos, -1);
    player->pos = dir_at(game->map, player->pos, player->dir);
    log_debug("Player %d moved to %d %d", player->number, player->pos.x,
        player->pos.y);
    change_players_tile(game->map, player->pos, 1);
}

void turn_right(game_t *game, player_t *player, event_t *event)
{
    (void)game;
    (void)event;
    if (player->dir < 1 || player->dir > 4)
        return;
    if (player->dir < 4)
        player->dir++;
    else
        player->dir = 1;
}

void turn_left(game_t *game, player_t *player, event_t *event)
{
    (void)game;
    (void)event;
    if (player->dir < 1 || player->dir > 4)
        return;
    if (player->dir > 1)
        player->dir--;
    else
        player->dir = 4;
}

void look(game_t *game, player_t *player, event_t *event)
{
    (void)game;
    (void)event;
    (void)player;
}