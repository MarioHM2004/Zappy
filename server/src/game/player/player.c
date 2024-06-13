/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** player
*/

#include "game/player.h"
#include "game/event.h"
#include "libs/log.h"
#include <sys/queue.h>

bool move_player(map_t *map,player_t *player, position_t new_pos)
{
    if (!change_players_tile(map, player->pos, -1))
        return false;
    if (!change_players_tile(map, player->pos, 1)) {
        change_players_tile(map, player->pos, 1);
        return false;
    }
    player->pos = new_pos;
    return true;
}

void player_tick(game_t *game, player_t *player)
{
    event_node_t *event_node = LIST_FIRST(player->events);

    log_player(player);
    if (event_node == NULL)
        return; // log_debug("has no events");
    //log_debug("has event %d ", event_node->event->type);
    if (event_node->wait_time > 0) {
        //log_debug("but needs to wait %d ticks", event_node->wait_time);
        event_node->wait_time--;
        return;
    }
    //log_debug("and is executing it");
    handle_ai_event(game, player, event_node->event);
    LIST_REMOVE(event_node, entries);
}
