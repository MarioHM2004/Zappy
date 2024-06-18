/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** broadcast
*/

#include "game/game.h"
#include "game/map.h"
#include "game/player.h"
#include "game/resources.h"
#include "libs/lib.h"
#include "libs/log.h"
#include "server/client.h"
#include "server/command.h"
#include "server/server.h"
#include "game/event.h"
#include <stdlib.h>

static sound_e determine_direction(position_t delta)
{
    if (delta.x == 0 && delta.y == 0)
        return 0;
    if (abs(delta.x) > abs(delta.y))
        return delta.x > 0 ? E : W;
    if (abs(delta.x) < abs(delta.y))
        return delta.y > 0 ? N : S;
    if (delta.x > 0 && delta.y > 0)
        return NE;
    if (delta.x < 0 && delta.y > 0)
        return NW;
    if (delta.x > 0 && delta.y < 0)
        return SE;
    else
        return SW;
}

static sound_e calculate_direction(map_t *map, player_t *from, player_t *to)
{
    position_t delta = {0};
    int delta_x_direct = to->pos.x - from->pos.x;
    int delta_y_direct = to->pos.y - from->pos.y;

    int delta_x_wrap = (to->pos.x - from->pos.x + map->width) % map->width -
        ((to->pos.x - from->pos.x + map->width) % map->width > map->width / 2 ? map->width : 0);
    int delta_y_wrap = (to->pos.y - from->pos.y + map->height) % map->height -
        ((to->pos.y - from->pos.y + map->height) % map->height > map->height / 2 ? map->height : 0);
    delta.x = abs(delta_x_wrap) < abs(delta_x_direct) ? delta_x_wrap : delta_x_direct;
    delta.y = abs(delta_y_wrap) < abs(delta_y_direct) ? delta_y_wrap : delta_y_direct;
    return determine_direction(delta);
}

static position_t sound_at(map_t *map, position_t pos, sound_e sound_dir)
{
    position_t new_pos = {.x = pos.x, .y = pos.y};

    if (sound_dir > 0 && sound_dir < 5)
        return dir_at(map, pos, (direction_e) sound_dir);
    switch (sound_dir) {
        case N:
            break;
        case S:
            break;
        case E:
            break;
        case W:
            break;
        case NE:
            new_pos.y--;
            new_pos.x++;
            return pos_at(map, new_pos);
        case SE:
            new_pos.y++;
            new_pos.x++;
            return pos_at(map, new_pos);
        case NW:
            new_pos.y--;
            new_pos.x--;
            return pos_at(map, new_pos);
        case SW:
            new_pos.y++;
            new_pos.x--;
            return pos_at(map, new_pos);
        break;
    }
    return new_pos;
}

static bool are_positions_equal(position_t pos1, position_t pos2)
{
    return pos1.x == pos2.x && pos1.y == pos2.y;
}

static int sound_trajectory(map_t *map, player_t *from, player_t *to)
{
    sound_e sound_dir = calculate_direction(map, from, to);
    position_t sound_trajectory = sound_at(map, to->pos, sound_dir);
    position_t tmp_pos = {0};
    direction_e tmp_dir;

    log_debug("Sound came from x: %d y: %d", sound_trajectory.x, sound_trajectory.y);
    if (are_positions_equal(to->pos, sound_trajectory))
        return 0;
    tmp_pos = dir_at(map, to->pos, to->dir);
    if (are_positions_equal(tmp_pos, sound_trajectory))
        return 1;
    tmp_dir = left_dir(to->dir);
    tmp_pos = dir_at(map, tmp_pos, tmp_dir);
    if (are_positions_equal(tmp_pos, sound_trajectory))
        return 2;
    tmp_dir = left_dir(tmp_dir);
    tmp_pos = dir_at(map, tmp_pos, tmp_dir);
    if (are_positions_equal(tmp_pos, sound_trajectory))
        return 3;
    tmp_pos = dir_at(map, tmp_pos, tmp_dir);
    if (are_positions_equal(tmp_pos, sound_trajectory))
        return 4;
    tmp_dir = left_dir(tmp_dir);
    tmp_pos = dir_at(map, tmp_pos, tmp_dir);
    if (are_positions_equal(tmp_pos, sound_trajectory))
        return 5;
    tmp_pos = dir_at(map, tmp_pos, tmp_dir);
    if (are_positions_equal(tmp_pos, sound_trajectory))
        return 6;
    tmp_dir = left_dir(tmp_dir);
    tmp_pos = dir_at(map, tmp_pos, tmp_dir);
    if (are_positions_equal(tmp_pos, sound_trajectory))
        return 7;
    tmp_pos = dir_at(map, tmp_pos, tmp_dir);
    if (are_positions_equal(tmp_pos, sound_trajectory))
        return 8;
    return -1;
}

void broadcast(server_t *server, player_t *player, event_t *event)
{
    player_node_t *tmp = NULL;
    client_t *client = get_client_by_fd(server->clients, player->fd);
    int sound_dir = 0;

    if (event->type != BROADCAST || !client)
        return;
    LIST_FOREACH(tmp, server->game->players, entries) {
        if (tmp->player == player || tmp->player->state != ALIVE)
            continue;
        sound_dir = sound_trajectory(server->game->map, player, tmp->player);
        if (sound_dir == -1) {
            log_debug("Error while sending message");
            continue;
        }
        log_debug("Player %d received %s from %d with dir %d", tmp->player->number,
            event->data.broadcast.text, sound_dir, tmp->player->dir);
        add_response_to_player(server->clients, tmp->player,
            formatstr(BROADCAST_RECEIVER, sound_dir, event->data.broadcast.text));
    }
    pbc_command(server, client, player, event->data.broadcast.text);
    add_response_to_player(server->clients, player, BROADCAST_SENDER);
}