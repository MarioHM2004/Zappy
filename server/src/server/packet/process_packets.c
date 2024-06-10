/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** process_packets
*/

#include "game/game.h"
#include "game/player.h"
#include "game/team.h"
#include "server/client.h"
#include "server/server.h"
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>
#include "libs/lib.h"
#include "server/socket.h"
#include "server/command.h"

// AI Protocol
static const client_command_t ai_commands[] = {
    {"Forward", &forward_command},
    {"Right", &right_command},
    {"Left", &left_command},
    {"Look", &look_command},
    {"Inventory", NULL},
    {"Broadcast", NULL},
    {"Connect_nbr", NULL},
    {"Fork", &fork_command},
    {"Eject", &eject_command},
    {"Take", &take_object_command},
    {"Set", &set_object_command},
    {"Incantation", &incantation_command},
    {"", NULL}
};

// GUI Protocol
static const client_command_t gui_commands[] = {
    {"msz", &msz_command},
    {"bct", &bct_command},
    {"mct", &mct_command},
    {"tna", &tna_command},
    {"ppo", &ppo_command},
    {"plv", &plv_command},
    {"pin", &pin_command},
    {"sgt", &sgt_command},
    {"sst", &sst_command},
    {"", NULL}
};

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
    // THIS GUI CLIENT
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
        // ebo
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

static void assign_client_type(server_t *server, client_t *client, char *cmd)
{
    packet_t *packet = NULL;
    packet_node_t *node = NULL;

    if (assign_graphic(server, client, cmd) || assign_team(server, client, cmd))
        return log_client(client);
    packet_message(client, ERROR_MESSAGE);
    client->socket->mode = WRITE;
}

static void client_command_ptr(server_t *server, client_t *client, char *cmd)
{
    const client_command_t *commands = NULL;

    if (client->type == PENDING)
        return assign_client_type(server, client, cmd);
    commands = (client->type == AI) ? ai_commands : gui_commands;
    for (size_t i = 0; commands[i].name[0]; i++) {
        if (startswith(cmd, commands[i].name))
            return commands[i].func(server, client, cmd);
    }
    packet_message(client, UNKNOWN_COMMAND);
}

void process_client_packets(server_t *server, client_t *client)
{
    char *cmd = NULL;

    while (!LIST_EMPTY(client->request)) {
        cmd = get_cmd_from_packets(client->request);
        client_command_ptr(server, client, cmd);
    }
}
