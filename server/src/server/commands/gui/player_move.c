/*
** EPITECH PROJECT, 2024
** gui
** File description:
** player_move
*/

#include "game/game.h"
#include "game/player.h"
#include "libs/lib.h"
#include "server/server.h"
#include "server/client.h"
#include "server/command.h"
#include <sys/queue.h>

void player_move(server_t *server, client_t *client, char *cmd)
{
    client_node_t *client_node = NULL;
    player_node_t *player_node = NULL;
    char *command = NULL;
    int player_number = 0;
    int x = 0;
    int y = 0;

    if (sscanf(cmd, PLAYER_MOVE_REQUEST, &player_number, &x, &y) == -1)
        return packet_message(client, INVALID_PARAMETERS);
    LIST_FOREACH(player_node, server->game->players, entries) {
        if (player_node->player->number == player_number)
            break;
    }
    if (!player_node)
        return packet_message(client, INVALID_PARAMETERS);
    move_player(server->game->map, player_node->player, (position_t){.x = x, .y = y});
    command = formatstr(PPO_REQUEST, player_number);
    if (!command)
        return packet_message(client, ERROR_MESSAGE);
    LIST_FOREACH(client_node, server->clients, entries) {
        if (client_node->client->type != GRAPHIC)
            continue;
        ppo_command(server, client_node->client, command);
    }
    free(command);
}

