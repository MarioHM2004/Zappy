/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** fork
*/

#include "game/event.h"
#include "game/game.h"
#include "game/player.h"
#include "libs/log.h"
#include "server/action.h"
#include "server/command.h"
#include <time.h>

void fork_command(server_t *server, client_t *client, char *cmd)
{
    player_t *player = get_player_by_fd(server->game->players, client->socket->fd);
    event_t *event = NULL;
    action_t *action = NULL;

    if (!player)
        return packet_message(client, ERROR_MESSAGE);
    event = create_event(FORK, (void *)player, sizeof(player_t));
    if (!event)
        return packet_message(client, ERROR_MESSAGE);
    action = create_action(PLAYER_FORK, player, sizeof(player_t *));
    add_action(server->actions, action);
    add_event(player->events, event, 42.0 / server->game->freq);
}
