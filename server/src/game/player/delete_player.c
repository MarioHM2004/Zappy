/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** game_delete
*/

#include "game/game.h"
#include "game/map.h"
#include "game/player.h"
#include "game/team.h"
#include "libs/log.h"
#include <stdlib.h>

void remove_player(game_t *game, player_t *player)
{
    team_t *team = get_team_by_player(game, player);

    if (!team)
        return;
    remove_player_from_team(team, player);
    if (player->state == EGG)
        change_eggs_tile(game->map, player->pos, -1);
    else
        change_players_tile(game->map, player->pos, -1);
    log_info("Player %d removed", player->number);
}

void destroy_player(player_t *p)
{
    if (p && p->inventory)
        destroy_resources(p->inventory);
    free(p);
}

void destroy_player_node(player_node_t *pn)
{
    if (pn && pn->player)
        destroy_player(pn->player);
    free(pn);
}

void destroy_player_list(player_list_t *head)
{
    player_node_t *node = NULL;
    player_node_t *tmp = NULL;

    if (!head)
        return;
    node = head->lh_first;
    while (node) {
        tmp = node;
        node = node->entries.le_next;
        destroy_player_node(tmp);
    }
    free(head);
}
