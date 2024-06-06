/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** pic
*/

#include "libs/lib.h"
#include "server/command.h"
#include "game/player.h"

void pic_command(server_t *server, client_t *client,
    player_t *player, int *p_number)
{
    packet_t *packet = NULL;
    char *response;
    char *p_nb_list;

    if (!player || !p_number)
        return packet_message(client, ERROR_MESSAGE);
    for (size_t i = 0; p_number[i]; i++) {
        p_nb_list = formatstr("%d", p_nb_list[i]);
        if (p_number[i + 1])
            p_nb_list = safe_strcat(p_nb_list, " ");
    }
    response = formatstr(PIC_RESPONSE, player->pos.x, player->pos.y,
    p_nb_list);
    if (!response)
        return packet_message(client, ERROR_MESSAGE);
    packet = create_packet(response);
    free(response);
    if (!packet)
        return packet_message(client, ERROR_MESSAGE);
    add_packet(client->response, packet);
}
