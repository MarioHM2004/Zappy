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
#include "server/command.h"

void fork_command(server_t *server, client_t *client, char *cmd)
{
    player_t *player = get_player_by_fd(server->game->players, client->socket->fd);
    event_t *event = NULL;

    if (!player)
        return packet_message(client, ERROR_MESSAGE);
    event = create_event(FORK, (void *)player, sizeof(player_t));
    if (!event)
        return packet_message(client, ERROR_MESSAGE);
    pfk_command(server, client, player);
    add_event(player->events, event, get_execution_time(42.0, server->game->freq));
}
