/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** msz
*/

#include "server/command.h"

void msz_command(server_t *server, client_t *client, char *cmd)
{
    packet_t *packet = create_packet(MSZ_RESPONSE(server->game->map->width, server->game->map->height));

    if (!packet)
        return;
    add_packet(client->response, packet);
}