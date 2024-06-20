/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** incantation
*/

#include "game/event.h"
#include "game/game.h"
#include "game/map.h"
#include "game/player.h"
#include "libs/lib.h"
#include "server/action.h"
#include "server/command.h"
#include "server/server.h"
#include "libs/log.h"
#include <sys/queue.h>
#include <time.h>

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

static void gui_incantation_action(server_t *server, player_list_t *player_list,
    player_t *player, bool success)
{
    action_t *action = NULL;
    incantation_action_t incantation = {
        .players = player_list,
        .state = success ? SUCCESSFUL : FAILED,
    };

    if (success) {
        action = create_action(INCANTATION_COMPLETE, &incantation,
            sizeof(incantation_action_t));
        add_action(server->actions, action);
    }
    action = create_action(INCANTATION_END, &incantation,
        sizeof(incantation_action_t));
    add_action(server->actions, action);
}

static void incantation_action(server_t *server, player_list_t *player_list,
    player_t *player, bool success)
{
    player_node_t *tmp = NULL;
    action_t *ai_action = NULL;

    if (!success) {
        ai_action = create_event_completed_action(player, END_INCANTATION,
            NULL, success);
        add_action(server->actions, ai_action);
        return;
    }
    LIST_FOREACH(tmp, player_list, entries) {
        ai_action = create_event_completed_action(tmp->player, END_INCANTATION,
            formatstr(END_INCANTATION_RESPONSE, tmp->player->level), success);
        add_action(server->actions, ai_action);
    }
    gui_incantation_action(server, player_list, player, success);
}

void incantation(server_t *server, player_t *player, event_t *event)
{
    tile_t tile = map_at(server->game->map, player->pos);
    player_list_t *players  = NULL;
    player_node_t *tmp = NULL;

    (void)event;
    if (!valid_incantation_tile(tile, incantations[player->level - 1])) {
        log_debug("%d: Invalid incantation\n", player->number);
        incantation_action(server, NULL, player, false);
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
    incantation_action(server, players, player, false);

}
