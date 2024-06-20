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
#include "libs/lib.h"
#include "libs/log.h"
#include "server/client.h"
#include "server/command.h"
#include "server/packet.h"
#include <sys/queue.h>
#include <time.h>
#include "game/event.h"

incantation_t incantations[INCANTATION_NUM] = {
    {1, 1, 1, 0, 0, 0, 0, 0},
    {2, 2, 1, 1, 1, 0, 0, 0},
    {3, 2, 2, 0, 1, 0, 2, 0},
    {4, 4, 1, 1, 2, 0, 1, 0},
    {5, 4, 1, 2, 1, 3, 0, 0},
    {6, 6, 1, 2, 3, 0, 1, 0},
    {7, 6, 2, 2, 2, 2, 2, 1}
};

bool valid_incantation_tile(tile_t tile, incantation_t incantation)
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

void incantation(server_t *server, player_t *player, event_t *event)
{
    tile_t tile = map_at(server->game->map, player->pos);
    player_list_t *players  = NULL;
    player_node_t *tmp = NULL;

    (void)event;
    if (!valid_incantation_tile(tile, incantations[player->level - 1])) {
        log_debug("%d: Invalid incantation\n", player->number);
        add_response_to_player(server->clients, player, ERROR_MESSAGE);
        return;
    }
    players = get_players_on_tile(server->game->players, player->pos, ALIVE);
    if (players == NULL)
        return;
    LIST_FOREACH(tmp, players, entries) {
        if (tmp->player->level == player->level)
            tmp->player->level++;
    }
    log_debug("%d: Incantation with %d players, level %d\n", player->number,
        player->number, get_player_list_size(players), player->level + 1);
    remove_incantation_items(tile.resource, player->level);
    add_response_to_player(server->clients, player,
        formatstr(END_INCANTATION_RESPONSE, player->level));
}

void fork_player(server_t *server, player_t *player, event_t *event)
{
    team_t *team = get_team_by_player(server->game, player);
    player_t *new_player = NULL;
    client_t *client = get_client_by_fd(server->clients, player->fd);

    if (!team || !client) {
        add_response_to_player(server->clients, player, ERROR_MESSAGE);
        return;
    }
    new_player = create_egg(server->game->map, player->pos);
    add_player_to_team(team, new_player);
    log_info("%d: An egg is laid in %d %d\n",
        player->number, player->pos.x, player->pos.y);
    enw_command(server, client, player, new_player);
    add_response_to_player(server->clients, player, FORK_RESPONSE);
}

static uint ejected_from(map_t *map, player_t *player, position_t pos)
{
    position_t tmp_pos = dir_at(map, player->pos, player->dir);

    log_debug("Ejecting from %d %d to %d %d", player->pos.x, player->pos.y,
        pos.x, pos.y);
    if (tmp_pos.x == pos.x && tmp_pos.y == pos.y)
        return 1;
    tmp_pos = dir_at(map, player->pos, right_dir(player->dir));
    if (tmp_pos.x == pos.x && tmp_pos.y == pos.y)
        return 7;
    tmp_pos = dir_at(map, player->pos, left_dir(player->dir));
    if (tmp_pos.x == pos.x && tmp_pos.y == pos.y)
        return 3;
    tmp_pos = dir_at(map, player->pos, right_dir(right_dir(player->dir)));
    if (tmp_pos.x == pos.x && tmp_pos.y == pos.y)
        return 5;
    log_error("Invalid eject direction");
    return 0;
}

static void egg_death(server_t *server, player_t *player)
{
    client_t *client = get_client_by_fd(server->clients, player->fd);

    if (!client) {
        log_error("Could not remove egg");
        return;
    }
    edi_command(server, client, player);
    remove_player(server->game, player);
}

void eject(server_t *server, player_t *player, event_t *event)
{
    tile_t tile = map_at(server->game->map, player->pos);
    position_t new_pos = dir_at(server->game->map, player->pos, player->dir);
    player_list_t *players =
        get_players_on_tile(server->game->players, player->pos, -1);
    player_node_t *tmp = NULL;
    uint ejected_pos = 0;

    if (tile.players == 1 || players == NULL) {
        add_response_to_player(server->clients, player, ERROR_MESSAGE);
        return;
    }
    LIST_FOREACH(tmp, players, entries) {
        if (tmp->player->number == player->number
            || tmp->player->state == DEAD)
            continue;
        if (tmp->player->state == EGG) {
            egg_death(server, tmp->player);
            continue;
        }
        ejected_pos = ejected_from(server->game->map, tmp->player, new_pos);
        move_player(server->game->map, tmp->player, new_pos);
        add_response_to_player(server->clients, tmp->player,
            formatstr(EJECTED_PLAYER, ejected_pos));
        log_debug("%d: Ejecting player %d", player->number, tmp->player->number);
    }
    add_response_to_player(server->clients, player, EJECT_RESPONSE);
}
