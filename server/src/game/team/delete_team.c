/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** team_delete
*/

#include "game/team.h"
#include <stdlib.h>
#include <sys/queue.h>

bool remove_player_from_team(team_t *team, player_t *player)
{
    player_node_t *tmp = NULL;

    if (!team || !player)
        return false;
    LIST_FOREACH(tmp, team->players, entries) {
        if (tmp->player == player) {
            LIST_REMOVE(tmp, entries);
            free(tmp);
            return true;
        }
    }
    return false;
}

void destroy_team(team_t *t)
{
    if (t && t->players)
        destroy_player_list(t->players);
    free(t);
}

void destroy_team_node(team_node_t *tn)
{
    if (tn && tn->team)
        destroy_team(tn->team);
    free(tn);
}

void destroy_team_list(team_list_t *head)
{
    team_node_t *node = NULL;
    team_node_t *tmp = NULL;

    if (!head)
        return;
    node = head->lh_first;
    while (node) {
        tmp = node;
        node = node->entries.le_next;
        destroy_team_node(tmp);
    }
    free(head);
}