/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** player_utils
*/

#include "game/event.h"
#include "game/player.h"
#include <stdbool.h>
#include <sys/queue.h>

bool append_event_to_player(event_t *event, player_t *player)
{
    event_node_t *event_node = create_event_node(event, 0.0);
    event_node_t *tmp = LIST_FIRST(player->events);

    if (!event_node || get_event_list_size(player->events) >= 10)
        return false;
    if (!tmp) {
        LIST_INSERT_HEAD(player->events, event_node, entries);
        return true;
    } else {
        while (LIST_NEXT(tmp, entries))
            tmp = LIST_NEXT(tmp, entries);
        LIST_INSERT_AFTER(tmp, event_node, entries);
        return true;
    }
    return true;
}