/*
** EPITECH PROJECT, 2024
** pending
** File description:
** pending
*/

#include "game/game.h"
#include "libs/log.h"
#include "server/client.h"
#include "server/server.h"
#include "game/player.h"
#include "server/command.h"
#include "libs/lib.h"
#include <string.h>
#include <time.h>

static void send_gui_player_info(server_t *server, client_t *client)
{
    player_node_t *node = NULL;
    char *command = NULL;

    if (!server->game->players)
        return;
    LIST_FOREACH(node, server->game->players, entries) {
        pnw_command(server, client, node->player);
        command = formatstr("plv %d", (int)node->player->number);
        plv_command(server, client, command);
        free(command);
        command = formatstr("pin %d", (int)node->player->number);
        pin_command(server, client, command);
        free(command);
    }
}

static bool assign_graphic(server_t *server, client_t *client, char *team)
{
    if (strcmp(team, GRAPHIC_TEAM_NAME) != 0)
        return false;
    client->type = GRAPHIC;
    msz_command(server, client, "msz");
    mct_command(server, client, "mct");
    tna_command(server, client, "tna");
    send_gui_player_info(server, client);
    sgt_command(server, client, "sgt");
    // eggs?
    // enw
    // eht
    return true;
}

static void send_guis_player_info(server_t *server, player_t *player)
{
    client_node_t *node = NULL;
    char *command = NULL;

    if (!player)
        return;
    command = formatstr("pin %d", player->number);
    LIST_FOREACH(node, server->clients, entries) {
        if (node->client->type != GRAPHIC)
            continue;
        pnw_command(server, node->client, player);
        pin_command(server, node->client, command);
        ebo_command(server, node->client, player);
        node->client->socket->mode = WRITE;
    }
    free(command);
}

static bool assign_team(server_t *server, client_t *client, char *team)
{
    team_node_t *node = NULL;
    player_t *player = NULL;

    LIST_FOREACH(node, server->game->teams, entries) {
        if (strcmp(node->team->name, team) != 0)
            continue;
        if (!player)
            continue;
        client->type = AI;
        player = assign_player(client->socket, server, team);
        if (!player) {
            log_error("No room for more players in team %s", team);
            return false;
        }
        log_info("Player %d joined team %s", player->number, team);
        log_debug("Pos x: %d, y: %d", player->pos.x, player->pos.y);
        pnw_command(server, client, player);
        msz_command(server, client, "msz");
        send_guis_player_info(server, player);
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

