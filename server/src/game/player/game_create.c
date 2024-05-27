/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** game_create
*/

#include "game/game.h"
#include <stdlib.h>
#include <sys/types.h>

player_t *create_player(socket_t *socket, uint number, uint x, uint y)
{
    player_t *player = calloc(1, sizeof(player_t));

    if (!player)
        return NULL;
    player->fd = socket->fd;
    player->number = number;
    player->x = x;
    player->y = y;
    player->dir = NORTH;
    player->level = 1;
    player->alive = true;
    player->inventory = create_resources();
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