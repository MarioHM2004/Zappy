/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** utils_team
*/

#include "game/game.h"
#include "game/team.h"

bool add_team(team_list_t *team_list, team_t *team)
{
    team_node_t *team_node = create_team_node(team);
    team_node_t *tmp = LIST_FIRST(team_list);

    if (!team_node)
        return false;
    if (!tmp) {
        LIST_INSERT_HEAD(team_list, team_node, entries);
        return true;
    } else {
        while (LIST_NEXT(tmp, entries))
            tmp = LIST_NEXT(tmp, entries);
        LIST_INSERT_AFTER(tmp, team_node, entries);
        return true;
    }
    return true;
}

uint get_team_list_size(team_list_t *head)
{
    uint size = 0;
    team_node_t *tmp = NULL;

    LIST_FOREACH(tmp, head, entries)
        size++;
    return size;
}