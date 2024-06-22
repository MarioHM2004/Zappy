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
#include "server/action.h"
#include "server/client.h"
#include "server/command.h"
#include "server/packet.h"
#include <stdbool.h>
#include <sys/queue.h>
#include <time.h>
#include "game/event.h"

static void fork_action(server_t *server, player_t *player, player_t *egg, bool success)
{
    action_t *ai_action = NULL;
    action_t *gui_action = NULL;
    egg_shell_t egg_shell = {
        .player = player,
        .egg = egg,
    };

    if (success) {
        ai_action = create_event_completed_action(player, FORK,
            FORK_RESPONSE, success);
        gui_action = create_action(EGG_LAYED, &egg, sizeof(egg_shell_t));
    } else
        ai_action = create_event_completed_action(player, FORK, NULL, false);
    if (ai_action)
        add_action(server->actions, ai_action);
    if (gui_action)
        add_action(server->actions, gui_action);
}

void fork_player(server_t *server, player_t *player, event_t *event)
{
    team_t *team = get_team_by_player(server->game, player);
    player_t *new_player = NULL;
    client_t *client = get_client_by_fd(server->clients, player->fd);

    if (!team || !client) {
        fork_action(server, player, new_player, false);
        return;
    }
    new_player = create_egg(server->game->map, player->pos);
    add_player_to_team(team, new_player);
    log_info("%d: An egg is laid in %d %d\n",
        player->number, player->pos.x, player->pos.y);
    fork_action(server, player, new_player, true);
}

