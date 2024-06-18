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
#include <sys/queue.h>

void pic_command(server_t *server, client_t *client,
    player_t *player, player_list_t *p_number)
{
    player_node_t *tmp = NULL;
    char *p_nb_list;
    char *response = NULL;

    if (!player || !p_number)
        return packet_message(client, ERROR_MESSAGE);
    LIST_FOREACH(tmp, p_number, entries) {
        p_nb_list = formatstr("%d", tmp->player->number);
        if (LIST_NEXT(tmp, entries))
            p_nb_list = safe_strcat(p_nb_list, " ");
    }
    response = formatstr(PIC_RESPONSE,
        (int)player->pos.x, (int)player->pos.y, p_nb_list);
    add_response(client, response);
    if (response)
        free(response);
}
