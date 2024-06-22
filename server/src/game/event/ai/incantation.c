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
    { .level = 1,  .players = 1, .linemate = 1, .deraumere = 0, .sibur = 0,
        .mendiane = 0, .phiras = 0, .thystame = 0 },
    { .level = 2,  .players = 2, .linemate = 1, .deraumere = 1, .sibur = 1,
        .mendiane = 0, .phiras = 0, .thystame = 0 },
    { .level = 3,  .players = 2, .linemate = 2, .deraumere = 0, .sibur = 1,
        .mendiane = 0, .phiras = 2, .thystame = 0 },
    { .level = 4,  .players = 4, .linemate = 1, .deraumere = 1, .sibur = 2,
        .mendiane = 0, .phiras = 1, .thystame = 0 },
    { .level = 5,  .players = 4, .linemate = 1, .deraumere = 2, .sibur = 1,
        .mendiane = 3, .phiras = 0, .thystame = 0 },
    { .level = 6,  .players = 6, .linemate = 1, .deraumere = 2, .sibur = 3,
        .mendiane = 0, .phiras = 1, .thystame = 0 },
    { .level = 7,  .players = 6, .linemate = 2, .deraumere = 2, .sibur = 2,
        .mendiane = 2, .phiras = 2, .thystame = 1 }
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

static void incantation_action(server_t *server, player_list_t *player_list,
    player_t *player, bool success)
{
    event_completed_t event_completed = {.type = END_INCANTATION,
        .player = player,
        .response = formatstr(END_INCANTATION_RESPONSE, player->level),
        .successful = success };
    incantation_action_t inc_action = { .players = player_list,
        .state = (success) ? SUCCESSFUL : FAILED };
    player_node_t *tmp = NULL;

    add_action(server->actions, create_action(EVENT_COMPLETED,
        &event_completed, sizeof(event_completed_t)));
    add_action(server->actions, create_action(INCANTATION_END,
        &inc_action, sizeof(incantation_action_t)));
    if (!success)
        return;
    LIST_FOREACH(tmp, player_list, entries) {
        if (tmp->player == player)
            continue;
        event_completed.player = tmp->player;
        add_action(server->actions, create_action(EVENT_COMPLETED,
            &event_completed, sizeof(event_completed_t)));
    }
    add_action(server->actions, create_action(INCANTATION_COMPLETE,
        &inc_action, sizeof(incantation_action_t)));
}

void incantation(server_t *server, player_t *player, event_t *event)
{
    log_debug("Incatation");
    tile_t tile = map_at(server->game->map, player->pos);
    player_list_t *players  = NULL;
    player_node_t *tmp = NULL;

    (void)event;
    players = get_players_on_tile(server->game->players, player->pos, ALIVE);
    if (!valid_incantation_tile(tile, incantations[player->level - 1])) {
        log_debug("%d: Invalid incantation\n", player->number);
        incantation_action(server, players, player, false);
        return;
    }
    if (players == NULL)
        return;
    LIST_FOREACH(tmp, players, entries) {
        if (tmp->player->level == player->level)
            tmp->player->level++;
    }
    log_debug("%d: Incantation with %d players, level %d\n", player->number,
        player->number, get_player_list_size(players), player->level + 1);
    remove_incantation_items(tile.resource, player->level);
    incantation_action(server, players, player, true);
}

