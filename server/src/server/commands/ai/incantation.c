/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** incantation
*/

#include "game/event.h"
#include "game/game.h"
#include "game/map.h"
#include "game/player.h"
#include "server/command.h"
#include <sys/queue.h>

void incantation_command(server_t *server, client_t *client, char *cmd)
{
    player_t *player = get_player_by_fd(server->game->players, client->socket->fd);
    player_node_t *tmp = NULL;
    player_list_t *player_list =
        get_players_on_tile(server->game->players, player->pos);
    event_t *event = NULL;
    tile_t tile = {0};

    if (!player)
        return packet_message(client, ERROR_MESSAGE);
    tile = map_at(server->game->map, player->pos);
    if (!valid_incantation_tile(tile, incantations[player->level - 1]))
        return packet_message(client, ERROR_MESSAGE);
    event = create_event(START_INCANTATION, (void *)player, sizeof(player_t));
    if (!event)
        return packet_message(client, ERROR_MESSAGE);
    LIST_FOREACH(tmp, player_list, entries)
        add_response_to_player(server->clients, tmp->player, START_INCANTATION_RESPONSE);
    pic_command(server, client, player, player_list);
    add_event(player->events, event, 300.0 / server->game->freq);
}
