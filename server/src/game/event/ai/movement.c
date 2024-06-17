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
#include "server/command.h"

void forward(server_t *server, player_t *player, event_t *event)
{
    position_t new_pos = dir_at(server->game->map, player->pos, player->dir);
    client_t *client = NULL;

    move_player(server->game->map, player, new_pos);
    log_debug("Player %d moved to %d %d", player->number, player->pos.x,
        player->pos.y);
    add_response_to_player(server->clients, player, FORWARD_RESPONSE);
}

direction_e right_dir(direction_e dir)
{
    if (dir < 4)
        dir++;
    else
        dir = 1;
    return dir;
}

void turn_right(server_t *server, player_t *player, event_t *event)
{
    (void)server;
    (void)event;
    if (player->dir < 1 || player->dir > 4)
        return;
    player->dir = right_dir(player->dir);
    add_response_to_player(server->clients, player, RIGHT_RESPONSE);
}

direction_e left_dir(direction_e dir)
{
    if (dir > 1)
        dir--;
    else
        dir = 4;
    return dir;
}

void turn_left(server_t *server, player_t *player, event_t *event)
{
    (void)server;
    (void)event;
    if (player->dir < 1 || player->dir > 4)
        return;
    player->dir = left_dir(player->dir);
    add_response_to_player(server->clients, player, LEFT_RESPONSE);
}
