/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** player_emvironment
*/

// incantation, broadcast, fork, eject

#include "game/player.h"
#include "game/game.h"
#include "game/map.h"
#include "game/resources.h"
#include "game/team.h"
#include "libs/log.h"
#include "server/command.h"
#include <sys/queue.h>
#include <time.h>

incantation_t incantations[] = {
    {1, 1, 1, 0, 0, 0, 0, 0},
    {2, 2, 1, 1, 1, 0, 0, 0},
    {3, 2, 2, 0, 1, 0, 2, 0},
    {4, 4, 1, 1, 2, 0, 1, 0},
    {5, 4, 1, 2, 1, 3, 0, 0},
    {6, 6, 1, 2, 3, 0, 1, 0},
    {7, 6, 2, 2, 2, 2, 2, 1}
};

static bool valid_incantation_tile(tile_t tile, incantation_t incantation)
{
    if (tile.players < incantation.players)
        return false;
    if (tile.resource->linemate < incantation.linemate)
        return false;
    if (tile.resource->deraumere < incantation.deraumere)
        return false;
    if (tile.resource->sibur < incantation.sibur)
        return false;
    if (tile.resource->mendiane < incantation.mendiane)
        return false;
    if (tile.resource->phiras < incantation.phiras)
        return false;
    if (tile.resource->thystame < incantation.thystame)
        return false;
    return true;
}

static void remove_incantation_items(resources_t *resource, int level)
{
    incantation_t incantation = incantations[level - 1];

    change_resource(resource, LINEMATE, -incantation.linemate);
    change_resource(resource, DERAUMERE, -incantation.deraumere);
    change_resource(resource, SIBUR, -incantation.sibur);
    change_resource(resource, MENDIANE, -incantation.mendiane);
    change_resource(resource, PHIRAS, -incantation.phiras);
    change_resource(resource, THYSTAME, -incantation.thystame);
}

void incantation(game_t *game, player_t *player, event_t *event)
{
    tile_t tile = map_at(game->map, player->pos);
    player_list_t *players  = NULL;
    player_node_t *tmp= NULL;

    (void)event;
    if (!valid_incantation_tile(tile, incantations[player->level - 1])) {
        log_debug("%d: Invalid incantation\n", player->number);
        return;
    }
    players = get_players_on_tile(game->players, player->pos);
    if (players == NULL)
        return;
    LIST_FOREACH(tmp, players, entries) {
        if (tmp->player->level == player->level)
            tmp->player->level++;
    }
    log_debug("%d: Incantation with %d players, level %d\n", player->number,
        player->number, get_player_list_size(players), player->level + 1);
    remove_incantation_items(tile.resource, player->level);
}

void broadcast(game_t *game, player_t *player, event_t *event)
{
    (void)game;
    (void)event;
    (void)player;
}

void fork_player(game_t *game, player_t *player, event_t *event)
{
    team_t *team = get_team_by_player(game, player);

    if (!team) {
        add_response_to_player(game->server->clients, player, ERROR_MESSAGE);
        log_error("%d: Player not in a team\n", player->number);
        return;
    }
    team->players++;
    change_eggs_tile(game->map, player->pos, 1);
    log_info("%d: An egg is laid in %d %d\n",
        player->number, player->pos.x, player->pos.y);
    add_response_to_player(game->server->clients, player, FORK_RESPONSE);
}

void eject(game_t *game, player_t *player, event_t *event)
{
    tile_t tile = map_at(game->map, player->pos);
    position_t new_pos = dir_at(game->map, player->pos, player->dir);
    player_list_t *players = NULL;
    player_node_t *tmp = NULL;

    (void)event;
    if (tile.players == 1) {
        log_debug("%d: No players to eject\n", player->number);
        return;
    }
    players = get_players_on_tile(game->players, player->pos);
    if (players == NULL)
        return;
    LIST_FOREACH(tmp, players, entries) {
        if (tmp->player->number == player->number)
            continue;
        move_player(game->map, tmp->player, new_pos);
        log_debug("%d: Ejecting player %d\n", player->number, tmp->player->number);
    }
}