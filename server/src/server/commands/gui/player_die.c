/*
** EPITECH PROJECT, 2024
** gui
** File description:
** player_die
*/

#include "game/game.h"
#include "game/player.h"
#include "server/server.h"
#include "server/client.h"
#include "server/command.h"
#include <sys/queue.h>

void player_die(server_t *server, client_t *client, char *cmd)
{
    client_node_t *client_node = NULL;
    player_node_t *player_node = NULL;
    client_t *player_client = NULL;
    int player_number = 0;

    if (sscanf(cmd, PLAYER_DIE_REQUEST, &player_number) == -1)
        return packet_message(client, INVALID_PARAMETERS);
    LIST_FOREACH(player_node, server->game->players, entries) {
        if (player_node->player->number == player_number)
            break;
    }
    if (!player_node)
        return packet_message(client, INVALID_PARAMETERS);
    player_client = get_client_by_fd(server->clients, player_node->player->fd);
    player_node->player->state = DEAD;
    add_response(player_client, DEATH_RESPONSE);
    LIST_FOREACH(client_node, server->clients, entries) {
        if (client_node->client->type != GRAPHIC)
            continue;
        pdi_command(server, client, player_node->player);
    }
}

