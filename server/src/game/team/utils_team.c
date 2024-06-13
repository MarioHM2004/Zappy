/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** utils_team
*/

#include "game/game.h"
#include "game/player.h"
#include "game/team.h"
#include <string.h>
#include <sys/queue.h>

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

team_t *get_team_by_player(game_t *game, player_t *player)
{
    team_node_t *tmp_team = NULL;
    player_node_t *tmp_player = NULL;

    LIST_FOREACH(tmp_team, game->teams, entries) {
        if (is_player_in_list(tmp_team->team->players, player))
            return tmp_team->team;
    }
    return NULL;
}

team_t *get_team_by_name(game_t *game, char *team_name)
{
    team_node_t *tmp = NULL;

    LIST_FOREACH(tmp, game->teams, entries) {
        if (strcmp(tmp->team->name, team_name) == 0)
            return tmp->team;
    }
    return NULL;

}

uint get_team_list_size(team_list_t *head)
{
    uint size = 0;
    team_node_t *tmp = NULL;

    LIST_FOREACH(tmp, head, entries)
        size++;
    return size;
}

void add_player_to_team(team_t *team, player_t *player)
{
    player_node_t *player_node = create_player_node(player);

    if (!player_node || !team)
        return;
    if (LIST_FIRST(team->players))
        LIST_INSERT_AFTER(LIST_FIRST(team->players), player_node, entries);
    else
        LIST_INSERT_HEAD(team->players, player_node, entries);
}
