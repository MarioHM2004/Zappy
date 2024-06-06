/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** game_create
*/

#include "game/map.h"
#include "game/player.h"
#include <stdlib.h>
#include <sys/types.h>

player_t *create_player(socket_t *socket, uint number, uint x, uint y)
{
    player_t *player = calloc(1, sizeof(player_t));

    if (!player)
        return NULL;
    player->fd = socket->fd;
    player->number = number;
    player->pos.x = x;
    player->pos.y = y;
    player->dir = NORTH;
    player->level = 1;
    player->state = ALIVE;
    player->inventory = create_resources();
    // player->events = create_event_list();
    if (player->inventory == NULL) {
        free(player);
        return NULL;
    }
    return player;
}

player_node_t *create_player_node(player_t *p)
{
    player_node_t *pn = calloc(1, sizeof(player_node_t));

    if (!pn)
        return NULL;
    pn->player = p;
    return pn;
}

player_list_t *create_player_list(void)
{
    player_list_t *head = calloc(1, sizeof(player_list_t));

    if (!head)
        return NULL;
    return head;
}
