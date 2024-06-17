/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** process_packets
*/

#include "game/game.h"
#include "libs/log.h"
#include "server/client.h"
#include "server/server.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>
#include "libs/lib.h"
#include "server/command.h"

// AI Protocol - response comes from the game
static const client_command_t ai_commands[] = {
    {"forward", &forward_command},
    {"right", &right_command},
    {"left", &left_command},
    {"look", &look_command},
    {"inventory", &inventory_command},
    {"broadcast", &broadcast_command},
    {"connect_nbr", &connect_nbr_command},
    {"fork", &fork_command},
    {"eject", &eject_command},
    {"take", &take_object_command},
    {"set", &set_object_command},
    {"incantation", &incantation_command},
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

static bool is_white_space(char c)
{
    if (isalpha(c))
        return false;
    return true;
}

static void client_command_ptr(server_t *server, client_t *client, char *cmd)
{
    const client_command_t *commands = NULL;

    if (client->type == PENDING)
        return assign_client_type(server, client, cmd);
    commands = (client->type == AI) ? ai_commands : gui_commands;
    for (size_t i = 0; commands[i].name[0]; i++) {
        if (!startswith(cmd, commands[i].name))
            continue;
        if (!is_white_space(cmd[strlen(commands[i].name)]))
            continue;
        return commands[i].func(server, client, cmd);
    }
    packet_message(client, UNKNOWN_COMMAND);
}

void process_client_packets(server_t *server, client_t *client)
{
    char *cmd = NULL;

    while (!LIST_EMPTY(client->request)) {
        cmd = get_cmd_from_packets(client->request);
        log_info("cmd=\"%s\"", cmd);
        client_command_ptr(server, client, cmd);
    }
}
