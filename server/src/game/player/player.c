/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** player
*/

#include "game/player.h"
#include "game/event.h"
#include <sys/queue.h>

void player_tick(game_t *game, player_t *player)
{
    event_node_t *event_node = LIST_FIRST(player->events);

    if (event_node == NULL)
        return;
    if (event_node->wait_time > 0) {
        event_node->wait_time--;
        return;
    }

    handle_ai_event(game, player, event_node->event);
    LIST_REMOVE(event_node, entries);
}
