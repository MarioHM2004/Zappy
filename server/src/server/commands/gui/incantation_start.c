/*
** EPITECH PROJECT, 2024
** gui
** File description:
** incantation_start
*/

#include "game/game.h"
#include "server/server.h"
#include "server/client.h"
#include "server/command.h"
#include "game/event.h"
#include <sys/queue.h>

void incantation_start_gui(server_t *server, client_t *client, char *cmd)
{
    event_t *event = NULL;
    player_node_t *node = NULL;
    int player_number = 0;

    if (sscanf(cmd, INCANTATION_START_REQUEST, &player_number) == -1)
        return packet_message(client, INVALID_PARAMETERS);
    LIST_FOREACH(node, server->game->players, entries) {
        if (node->player->number == player_number)
            break;
    }
    event = create_event(START_INCANTATION, node->player, sizeof(player_t));
    if (!event)
        return;
    add_event(node->player->events, event,
        get_execution_time(300, server->game->freq));
}

