/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** player_utils
*/

#include "game/event.h"
#include "game/game.h"
#include "game/player.h"
#include <stdbool.h>
#include <sys/queue.h>


bool add_player(player_list_t *player_list, player_t *player)
{
    player_node_t *player_node = create_player_node(player);
    player_node_t *tmp = LIST_FIRST(player_list);

    if (!player_node)
        return false;
    if (!tmp) {
        LIST_INSERT_HEAD(player_list, player_node, entries);
        return true;
    } else {
        while (LIST_NEXT(tmp, entries))
            tmp = LIST_NEXT(tmp, entries);
        LIST_INSERT_AFTER(tmp, player_node, entries);
        return true;
    }
    return true;
}

bool add_event_to_player(event_t *event, player_t *player)
{
    bool status = false;

    if (get_event_list_size(player->events) >= 10)
        return status;
    return add_event(player->events, event);
}

uint get_player_list_size(player_list_t *head)
{
    uint size = 0;
    player_node_t *tmp = NULL;

    LIST_FOREACH(tmp, head, entries)
        size++;
    return size;
}