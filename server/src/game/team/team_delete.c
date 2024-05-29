/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** team_delete
*/

#include "game/team.h"
#include <stdlib.h>

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