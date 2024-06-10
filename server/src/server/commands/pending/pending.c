/*
** EPITECH PROJECT, 2024
** pending
** File description:
** pending
*/

#include "game/game.h"
#include "server/client.h"
#include "server/server.h"
#include "game/player.h"
#include "server/command.h"
#include "libs/lib.h"
#include <string.h>

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

static void send_guis_player_info(server_t *server, client_t *client)
{
    client_node_t *node = NULL;
    player_t *player = get_player_by_fd(server->game->players, client->socket->fd);
    char *command = formatstr("pin %d", player->number);

    if (!player)
        return;
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
        client->type = AI;
        player = create_player(client->socket, 0, 0, 0);
        add_player(server->game->players, player);
        add_player_to_team(node->team, player);
        send_guis_player_info(server, client);
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

