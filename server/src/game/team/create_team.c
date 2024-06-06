/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** team_create
*/

#include "game/team.h"
#include <stdlib.h>
#include <string.h>


team_list_t *init_teams(char **teams)
{
    team_list_t *head = create_team_list();
    team_t *team;

    for (int i = 0; teams[i]; i++) {
        team = create_team(teams[i]);
        add_team(head, team);
    }
    return head;
}

team_t *create_team(const char *name)
{
    team_t *team = calloc(1, sizeof(team_t));

    if (!team)
        return NULL;
    strcpy(team->name, name);
    team->players = create_player_list();
    if (!team->players) {
        free(team);
        return NULL;
    }
    return team;
}

team_node_t *create_team_node(team_t *t)
{
    team_node_t *tn = calloc(1, sizeof(team_node_t));

    if (!tn)
        return NULL;
    tn->team = t;
    return tn;
}

team_list_t *create_team_list(void)
{
    team_list_t *head = calloc(1, sizeof(team_list_t));

    if (!head)
        return NULL;
    LIST_INIT(head);
    return head;
}
