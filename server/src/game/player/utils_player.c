/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** player_utils
*/

#include "game/event.h"
#include "game/game.h"
#include "game/player.h"
#include "libs/log.h"
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

uint get_player_list_size(player_list_t *head)
{
    uint size = 0;
    player_node_t *tmp = NULL;

    LIST_FOREACH(tmp, head, entries)
        size++;
    return size;
}

bool is_player_in_list(player_list_t *head, player_t *player)
{
    player_node_t *tmp = NULL;

    LIST_FOREACH(tmp, head, entries) {
        if (tmp->player == player)
            return true;
    }
    return false;
}

player_t *get_player_by_fd(player_list_t *players, int fd)
{
    player_node_t *node = NULL;

    LIST_FOREACH(node, players, entries) {
        if (node->player->fd == fd)
            return node->player;
    }
    return NULL;
}
