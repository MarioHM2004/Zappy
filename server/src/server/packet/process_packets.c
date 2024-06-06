/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** process_packets
*/

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
    {"Forward", NULL},
    {"Right", NULL},
    {"Left", NULL},
    {"Look", NULL},
    {"Inventory", NULL},
    {"Broadcast", NULL},
    {"Connect_nbr", NULL},
    {"Fork", NULL},
    {"Eject", NULL},
    {"Take", NULL},
    {"Set", NULL},
    {"Incantation", NULL},
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

static bool assign_graphic(server_t *server, client_t *client, char *team)
{
    if (strcmp(team, GRAPHIC_TEAM_NAME) != 0)
        return false;
    client->type = GRAPHIC;
    // THIS GUI CLIENT
    msz_command(server, client, "msz");
    mct_command(server, client, "mct");
    tna_command(server, client, "tna");
    // pnw
    // plv /* all players? */
    // pin /* all players? */
    // enw
    sgt_command(server, client, "sgt");
    // eht
    return true;
}

static bool assign_team(server_t *server, client_t *client, char *team)
{
    team_node_t *node = NULL;

    LIST_FOREACH(node, server->game->teams, entries) {
        if (strcmp(node->team->name, team) == 0) {
            client->type = AI;
            // asing player to team
            // ALL GUI CLIENTS
            // pnw
            // pin
            // ebo
            return true;
        }
    }
    return false;
}

static void assign_client_type(server_t *server, client_t *client, char *cmd)
{
    packet_t *packet = NULL;
    packet_node_t *node = NULL;

    if (assign_graphic(server, client, cmd) || assign_team(server, client, cmd))
        return log_client(client);
    packet_message(client, "UNKNOWN TEAM");
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
