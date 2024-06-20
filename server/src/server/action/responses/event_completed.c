/*
** EPITECH PROJECT, 2024
** responses
** File description:
** event_completed
*/

#include "server/client.h"
#include "server/command.h"
#include "server/server.h"
#include "server/action.h"
#include <stdlib.h>

action_t *create_event_completed_action(player_t *player,
    event_type_e event_type, char *response, bool successful)
{
    event_completed_t event_completed = {
        .type = event_type,
        .response = response,
        .successful = successful,
        .player = player
    };
    action_t *action = create_action(EVENT_COMPLETED, &event_completed,
        sizeof(event_completed_t));

    return action;
}

void event_completed(server_t *server, action_t *action)
{
    client_t *client = NULL;

    if (!server || !action)
        return;
    client = get_client_by_fd(server->clients,
        action->data.event_completed.player->fd);
    if (!client)
        return;
    if (!action->data.event_completed.successful)
        return add_response(client, ERROR_MESSAGE);
    return add_response(client, action->data.event_completed.response);
}

