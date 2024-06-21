/*
** EPITECH PROJECT, 2024
** responses
** File description:
** event_completed
*/

#include "game/event.h"
#include "server/client.h"
#include "server/command.h"
#include "server/server.h"
#include "server/action.h"
#include "libs/lib.h"
#include <stdlib.h>
#include <sys/queue.h>

static void tmp(server_t *server, action_t *action);

static const action_event_t action_events[] = {
    { FORWARD, &player_moved },
    { TURN_RIGHT, &player_moved },
    { TURN_LEFT, &player_moved },
};

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
    size_t len = sizeof(action_events) / sizeof(action_events[0]);

    if (!server || !action)
        return;
    client = get_client_by_fd(server->clients,
        action->data.event_completed.player->fd);
    if (!client)
        return;
    if (!action->data.event_completed.successful)
        return add_response(client, ERROR_MESSAGE);
    add_response(client, action->data.event_completed.response);
    for (size_t i = 0; i < len; i++) {
        if (action->data.event_completed.type != action_events[i].type)
            continue;
        action_events[i].func(server, action);
    }
}

