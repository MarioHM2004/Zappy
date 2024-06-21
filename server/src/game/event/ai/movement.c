/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** movement
*/

#include "game/event.h"
#include "game/game.h"
#include "game/map.h"
#include "game/player.h"
#include "libs/log.h"
#include "server/action.h"
#include "server/command.h"
#include <stdbool.h>

void forward(server_t *server, player_t *player, event_t *event)
{
    position_t new_pos = dir_at(server->game->map, player->pos, player->dir);
    event_completed_t event_completed = {
        .player = player, .type = event->type, .response = FORWARD_RESPONSE,
        .successful = true
    };
    action_t *action = create_action(EVENT_COMPLETED, &event_completed,
        sizeof(event_completed_t));

    if (!action)
        return;
    move_player(server->game->map, player, new_pos);
    log_debug("Player %d moved to %d %d", player->number, player->pos.x,
        player->pos.y);
    add_action(server->actions, action);
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
    event_completed_t event_completed = {
        .player = player, .type = event->type, .response = RIGHT_RESPONSE,
        .successful = true
    };
    action_t *action = create_action(EVENT_COMPLETED, &event_completed,
        sizeof(event_completed_t));

    (void)event;
    if (!action)
        return;
    if (player->dir < 1 || player->dir > 4)
        return;
    player->dir = right_dir(player->dir);
    add_action(server->actions, action);
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
    event_completed_t event_completed = {
        .player = player, .type = event->type, .response = LEFT_RESPONSE,
        .successful = true
    };
    action_t *action = create_action(EVENT_COMPLETED, &event_completed,
        sizeof(event_completed_t));

    (void)event;
    if (!action)
        return;
    if (player->dir < 1 || player->dir > 4)
        return;
    player->dir = left_dir(player->dir);
    add_action(server->actions, action);
}

