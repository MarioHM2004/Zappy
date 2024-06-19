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
    return add_response(client, action.data.event_completed.response);
}

