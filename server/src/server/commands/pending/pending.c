/*
** EPITECH PROJECT, 2024
** pending
** File description:
** pending
*/

#include "game/game.h"
#include "libs/log.h"
#include "server/action.h"
#include "server/client.h"
#include "server/server.h"
#include "game/player.h"
#include "server/command.h"
#include <string.h>
#include <time.h>

static bool assign_graphic(server_t *server, client_t *client, char *team)
{
    action_t *action = NULL;

    if (strcmp(team, GRAPHIC_TEAM_NAME) != 0)
        return false;
    client->type = GRAPHIC;
    action = create_action(NEW_GUI, client, sizeof(client_t));
    if (!action)
        return false;
    add_action(server->actions, action);
    return true;
}

static bool assign_team(server_t *server, client_t *client, char *team)
{
    team_node_t *node = NULL;
    player_t *player = NULL;
    action_t *action = NULL;

    LIST_FOREACH(node, server->game->teams, entries) {
        if (strcmp(node->team->name, team) != 0)
            continue;
        client->type = AI;
        player = assign_player(client->socket, server, team);
        if (!player)
            return false;
        log_info("Player %d joined team %s", player->number, team);
        action = create_action(NEW_PLAYER, client, sizeof(client_t));
        if (!action)
            return false;
        add_action(server->actions, action);
        return true;
    }
    return false;
}

void assign_client_type(server_t *server, client_t *client, char *cmd)
{
    packet_t *packet = NULL;
    packet_node_t *node = NULL;

    if (assign_graphic(server, client, cmd) || assign_team(server, client, cmd))
        return log_client(client);
    packet_message(client, ERROR_MESSAGE);
    client->socket->mode = WRITE;
}

