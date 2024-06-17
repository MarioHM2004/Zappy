/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** pin
*/

#include "libs/lib.h"
#include "server/command.h"
#include "game/player.h"

static char *get_pin(server_t *server, int player)
{
    player_node_t *tmp = NULL;

    if (!server->game->players)
        return NULL;
    LIST_FOREACH(tmp, server->game->players, entries) {
        if ((int)tmp->player->number != player)
            continue;
        return formatstr(PIN_RESPONSE, player,
            (int)tmp->player->pos.x,
            (int)tmp->player->pos.y,
            (int)tmp->player->inventory->food,
            (int)tmp->player->inventory->linemate,
            (int)tmp->player->inventory->deraumere,
            (int)tmp->player->inventory->sibur,
            (int)tmp->player->inventory->mendiane,
            (int)tmp->player->inventory->phiras,
            (int)tmp->player->inventory->thystame
            );
    }
    return NULL;
}

void pin_command(server_t *server, client_t *client, char *cmd)
{
    char *response = NULL;
    int player = 0;

    if (sscanf(cmd, PIN_REQUEST, &player) == -1)
        return packet_message(client, INVALID_PARAMETERS);
    response = get_pin(server, player);
    add_response(client, response);
    if (response)
        free(response);
}
