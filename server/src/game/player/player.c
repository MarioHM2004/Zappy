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

void player_tick(game_t *game, player_t *player)
{
    event_node_t *event_node = LIST_FIRST(player->events);

    log_debug("Player with fd %d, ", player->fd);
    if (event_node == NULL) {
        log_debug("has no events\n");
        return;
    }
    log_debug("has event %d ", event_node->event->type);
    if (event_node->wait_time > 0) {
        log_debug("but needs to wait %d ticks\n", event_node->wait_time);
        event_node->wait_time--;
        return;
    }
    log_debug("and is executing it\n");
    handle_ai_event(game, player, event_node->event);
    LIST_REMOVE(event_node, entries);
}
