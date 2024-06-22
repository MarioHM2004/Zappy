/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** eject
*/

#include "game/event.h"
#include "game/game.h"
#include "game/player.h"
#include "libs/lib.h"
#include "libs/log.h"
#include "server/action.h"
#include "server/command.h"
#include "server/server.h"
#include <stdbool.h>
#include <time.h>

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

static void handle_egg_death(server_t *server, player_t *player)
{
    action_t *action = create_action(EGG_DEATH, player, sizeof(player_t *));

    if (action == NULL)
        return;
    add_action(server->actions, action);
    remove_player(server->game, player);
}

static void eject_action(server_t *server, player_t *player,
    player_list_t *player_list, int *eject_dir)
{
    action_t *action = NULL;
    eject_t eject = {
        .player = player,
        .players = player_list,
        .eject_dir = eject_dir
    };

    if (player_list)
        action = create_action(PLAYER_EJECT,
            &eject, sizeof(eject_t));
    else
        action = create_event_completed_action(player, EJECT,
            NULL, false);
    if (action)
        add_action(server->actions, action);
}

void eject(server_t *server, player_t *player, event_t *event)
{
    tile_t tile = map_at(server->game->map, player->pos);
    position_t new_pos = dir_at(server->game->map, player->pos, player->dir);
    player_list_t *players =
        get_players_on_tile(server->game->players, player->pos, -1);
    player_node_t *tmp = NULL;
    uint ejected_pos = 0;
    int *eject_dir = calloc(get_player_list_size(players), sizeof(int));
    uint count = 0;

    if (tile.players == 1 || players == NULL) {
        eject_action(server, player, NULL, NULL);
        return;
    }
    LIST_FOREACH(tmp, players, entries) {
        if (tmp->player->number == player->number
            || tmp->player->state == DEAD)
            continue;
        if (tmp->player->state == EGG) {
            handle_egg_death(server, tmp->player);
            continue;
        }
        ejected_pos = ejected_from(server->game->map, tmp->player, new_pos);
        eject_dir[count] = ejected_pos;
        move_player(server->game->map, tmp->player, new_pos);
        log_debug("%d: Ejecting player %d", player->number, tmp->player->number);
        count++;
    }
    eject_action(server, player, players, eject_dir);
}
