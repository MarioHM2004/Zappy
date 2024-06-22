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
#include "libs/log.h"
#include "server/action.h"
#include "server/command.h"
#include <stdbool.h>
#include <sys/queue.h>
#include <time.h>

static void incantation_start_action(server_t *server,
    player_list_t *player_list, player_t *player, bool success)
{
    player_node_t *tmp;
    action_t *ai_action = NULL;
    action_t *gui_action = NULL;
    incantation_action_t incantation = {
        .players = player_list,
        .state = IN_PROGRESS,
    };

    if (success) {
        LIST_FOREACH(tmp, player_list, entries) {
            ai_action = create_event_completed_action(tmp->player,
                START_INCANTATION, START_INCANTATION_RESPONSE, success);
            add_action(server->actions, ai_action);
        }
        gui_action = create_action(INCANTATION_START, &incantation,
            sizeof(incantation_action_t));
        add_action(server->actions, gui_action);
    } else {
        ai_action = create_event_completed_action(player, START_INCANTATION,
            NULL, success);
        add_action(server->actions, ai_action);
    }
}

void incantation_command(server_t *server, client_t *client, char *cmd)
{
    player_t *player = get_player_by_fd(server->game->players, client->socket->fd);
    player_node_t *tmp = NULL;
    player_list_t *player_list =
        get_players_on_tile(server->game->players, player->pos, ALIVE);
    event_t *event = NULL;
    tile_t tile = {0};

    if (!player)
        return packet_message(client, ERROR_MESSAGE);
    tile = map_at(server->game->map, player->pos);
    if (!valid_incantation_tile(tile, incantations[player->level - 1]))
        return packet_message(client, ERROR_MESSAGE);
    event = create_event(START_INCANTATION, (void *)player, sizeof(player_t));
    if (!event)
        return packet_message(client, ERROR_MESSAGE);
    incantation_start_action(server, player_list, player, true);
    add_event(player->events, event, 300.0 / server->game->freq);
}
