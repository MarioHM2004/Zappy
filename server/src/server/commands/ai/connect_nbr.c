/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** connect_nbr
*/

#include "game/event.h"
#include "game/game.h"
#include "game/player.h"
#include "game/team.h"
#include "libs/lib.h"
#include "libs/log.h"
#include "server/command.h"
#include <sys/types.h>
#include <time.h>


static uint get_team_unused_spots(player_list_t *head)
{
    uint size = 0;
    player_node_t *tmp = NULL;

    LIST_FOREACH(tmp, head, entries) {
        if (tmp->player->state == EGG)
            size++;
    }
    return size;
}

void connect_nbr_command(server_t *server, client_t *client, char *cmd)
{
    player_t *player = get_player_by_fd(server->game->players, client->socket->fd);
    event_t *event = NULL;
    team_t *team = NULL;
    uint size = 0;

    if (!player) {
        log_error("Player not found");
        return packet_message(client, ERROR_MESSAGE);
    }
    team = get_team_by_player(server->game, player);
    if (!team) {
        log_error("Team not found");
        return packet_message(client, ERROR_MESSAGE);
    }
    size = get_team_unused_spots(team->players);
    return packet_message(client, formatstr(CONNECT_NBR_RESPONSE, size));
}
