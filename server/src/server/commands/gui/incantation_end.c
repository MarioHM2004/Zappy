/*
** EPITECH PROJECT, 2024
** gui
** File description:
** incantation_end
*/

#include "game/event.h"
#include "server/command.h"
#include "server/server.h"
#include "server/client.h"
#include <sys/queue.h>

void incantation_end_gui(server_t *server, client_t *client, char *cmd)
{
    player_node_t *node = NULL;
    event_t *event = NULL;
    int player_number = 0;

    if (sscanf(cmd, INCANTATION_END_REQUEST, &player_number) == -1)
        return packet_message(client, INVALID_PARAMETERS);
    LIST_FOREACH(node, server->game->players, entries) {
        if (node->player->number == player_number)
            break;
    }
    if (!node)
        return packet_message(client, ERROR_MESSAGE);
    event = create_event(END_INCANTATION, node->player, sizeof(player_t));
    if (!event)
        return;
    add_event(node->player->events, event,
        get_execution_time(0, server->game->freq));
}
