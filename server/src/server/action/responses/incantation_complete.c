/*
** EPITECH PROJECT, 2024
** responses
** File description:
** incantation_complete
*/

#include "libs/lib.h"
#include "server/client.h"
#include "server/command.h"
#include "server/server.h"
#include "server/action.h"
#include <sys/queue.h>

action_t *create_incantation_complete(player_list_t *players)
{
    incantation_action_t incantation = {
        .players = players,
        .state = SUCCESSFUL
    };
    action_t *action = create_action(INCANTATION_COMPLETE,
        &incantation, sizeof(incantation_action_t));


    return action;
}

void incantation_complete(server_t *server, action_t *action)
{
    client_node_t *client_node = NULL;
    player_node_t *player_node = NULL;
    char *command = NULL;

    if (!server || !action)
        return;
    LIST_FOREACH(client_node, server->clients, entries) {
        if (client_node->client->type != GRAPHIC)
            continue;
        LIST_FOREACH(player_node, action->data.incantation.players, entries) {
            command = formatstr(PLV_REQUEST, player_node->player->number);
            if (!command)
                continue;
            plv_command(server, client_node->client, command);
            free(command);
        }
    }
}

