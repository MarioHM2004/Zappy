/*
** EPITECH PROJECT, 2024
** player
** File description:
** log_player
*/

#include "game/game.h"
#include "game/map.h"
#include "game/player.h"
#include "libs/log.h"

void log_player(player_t *player)
{
    char *dir = NULL;
    char *state = NULL;

    if (!player)
        return;
    if (player->dir == NORTH)
        dir = "NORTH";
    if (player->dir == EAST)
        dir = "EAST";
    if (player->dir == SOUTH)
        dir = "SOUTH";
    if (player->dir == WEST)
        dir = "WEST";
    if (player->state == ALIVE)
        state = "ALIVE";
    if (player->state == DEAD)
        state = "DEAD";
    if (player->state == EGG)
        state = "EGG";
    log_info("Player={fd=%d, number=%d, level=%d, position={x=%d, y=%d}, dir=%s, state=%s}",
        player->fd, player->number, player->level, player->pos.x, player->pos.y, dir, state);
}

