/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** process_packets
*/

#include "server/server.h"
#include <stdlib.h>
#include <string.h>
#include "libs/lib.h"
#include "zappy.h"
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
};

// GUI Protocol
static const client_command_t gui_commands[] = {
    {"msz", NULL},
    {"bct", NULL},
    {"mct", NULL},
    {"tna", NULL},
    {"ppo", NULL},
    {"plv", NULL},
    {"pin", NULL},
    {"sgt", NULL},
    {"sst", NULL}
}

static bool is_packed_completed(packet_t *packet)
{
    if (!packet)
        return false;
    for (size_t i = 0; packet->data[i]; i++) {
        if (strstr(packet->data, CRLF))
            return true;
    }
    return false;
}

char *get_cmd_from_packets(packet_list_t *packets)
{
    char *cmd = calloc(MAX_COMMAND_LENGTH, sizeof(char));
    packet_node_t *tmp = NULL;
    packet_node_t *current = NULL;

    if (!packets)
        return NULL;
    strcpy(cmd, packets->lh_first->packet->data);
    current = LIST_FIRST(packets);
    while (current != NULL) {
        tmp = LIST_NEXT(current, entries);
        LIST_REMOVE(current, entries);
        if (!current->packet || is_packed_completed(current->packet))
            break;
        cmd = safe_strcat(cmd, current->packet->data);
        destroy_packet_node(current);
        current = tmp;

    }
    return cmd;
}

static void client_command_ptr(server_t *server, client_t *client, char *cmd)
{
    client_command_t commands = NULL;

    switch (client->type) {
        case PENDING:
            break;
        case AI:
            commands = ai_commands;
            break;
        case GRAPHIC:
            commands = gui_commands;
            break;
    }
    for (size_t i = 0; commands[i]; i++) {
        if (startswith(cmd, commands[i].name))
            commands[i].func(server, client, cmd);
    }
}

void process_client_packets(server_t *server, client_t *client)
{
    char *cmd = NULL;

    while (!LIST_EMPTY(client->request)) {
        cmd = get_cmd_from_packets(client->request);
        client_command_ptr(server, client, cmd);
    }
}
