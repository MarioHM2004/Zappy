/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** pic
*/

#include "game/game.h"
#include "libs/lib.h"
#include "server/command.h"
#include "game/player.h"
#include <stdlib.h>
#include <sys/queue.h>

void pic_command(server_t *server, client_t *client, player_list_t *players)
{
    player_node_t *node = NULL;
    char *player_numbers = calloc(1, sizeof(char));
    char *response = NULL;

    if (!players || !player_numbers)
        return packet_message(client, ERROR_MESSAGE);
    LIST_FOREACH(node, players, entries) {
        player_numbers = safe_strcat(player_numbers,
            formatstr("%d", node->player->number)();
        if (LIST_NEXT(node, entries))
            player_numbers = safe_strcat(player_numbers, " ");
    }
    response = formatstr(PIC_RESPONSE,
        (int)LIST_FIRST(players)->player->pos.x, 
        (int)LIST_FIRST(players)->player->pos.y, player_numbers);
    add_response(client, response);
    if (response)
        free(response);
}
