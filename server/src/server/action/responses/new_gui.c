/*
** EPITECH PROJECT, 2024
** responses
** File description:
** new_gui
*/

#include "libs/lib.h"
#include "server/command.h"
#include "server/server.h"
#include "server/action.h"

static void players_info(server_t *server, client_t *client)
{
    player_node_t *node = NULL;
    char *command = NULL;

    if (!server->game->players)
        return;
    LIST_FOREACH(node, server->game->players, entries) {
        pnw_command(server, client, node->player);
        command = formatstr("plv %d", (int)node->player->number);
        if (!command)
            continue;
        plv_command(server, client, command);
        free(command);
        command = formatstr("pin %d", (int)node->player->number);
        if (!command)
            continue;
        pin_command(server, client, command);
        free(command);
    }
}

void new_gui(server_t *server, action_t *action)
{
    if (!server || !action)
        return;

    msz_command(server, action->data.client, "msz");
    mct_command(server, action->data.client, "mct");
    tna_command(server, action->data.client, "tna");
    players_info(server, action->data.client);
    sgt_command(server, action->data.client, "sgt");
    // eggs?
    // enw
    // eht
}

