/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** broadcast
*/

#include "game/event.h"
#include "game/game.h"
#include "game/player.h"
#include "libs/log.h"
#include "server/command.h"

void broadcast_command(server_t *server, client_t *client, char *cmd)
{
    player_t *player = get_player_by_fd(server->game->players, client->socket->fd);
    broadcast_t *broadcast = NULL;
    event_t *event = NULL;
    char broadcast_text[MAX_BROADCAST_LENGTH];

    if (sscanf(cmd, "broadcast %1023s", broadcast_text) == -1) {
        return packet_message(client, ERROR_MESSAGE);
    }
    broadcast = create_broadcast(player, broadcast_text);
    if (!player || !broadcast)
        return packet_message(client, ERROR_MESSAGE);
    event = create_event(BROADCAST, (void *)broadcast, sizeof(broadcast_t));
    if (!event)
        return packet_message(client, ERROR_MESSAGE);
    add_event(player->events, event,
        get_execution_time(7.0, server->game->freq));
}
