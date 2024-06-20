/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** take_object
*/

#include "game/event.h"
#include "game/game.h"
#include "game/player.h"
#include "libs/log.h"
#include "server/command.h"

void take_object_command(server_t *server, client_t *client, char *cmd)
{
    player_t *player = get_player_by_fd(server->game->players, client->socket->fd);
    object_t *object = NULL;
    event_t *event = NULL;
    char cmd_object[MAX_OBJECT_LENGTH];

    if (sscanf(cmd, "take %15s", cmd_object) == -1)
        return packet_message(client, ERROR_MESSAGE);
    object = create_object(player, cmd_object);
    if (!player || !object)
        return packet_message(client, ERROR_MESSAGE);
    event = create_event(TAKE_OBJECT, (void *)object, sizeof(object_t));
    if (!event)
        return packet_message(client, ERROR_MESSAGE);
    add_event(player->events, event, get_execution_time(7.0, server->game->freq));
}