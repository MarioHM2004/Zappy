/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** event_received
*/

#include "server/action.h"
#include "server/command.h"
#include "server/server.h"

action_t *create_event_received_action(player_t *player,
    event_received_type_e event_type, char *response, bool successful)
{
    event_received_t event_received = {
        .type = event_type,
        .response = response,
        .successful = successful,
        .player = player
    };
    action_t *action = create_action(EVENT_RECEIVED, &event_received,
        sizeof(event_received_t));

    return action;
}

void event_received(server_t *server, action_t *action)
{
    client_t *client = NULL;

    if (!server || !action)
        return;
    client = get_client_by_fd(server->clients,
        action->data.event_completed.player->fd);
    if (!client)
        return;
    if (!action->data.event_received.successful)
        return add_response(client, ERROR_MESSAGE);
    return add_response(client, action->data.event_received.response);
}

