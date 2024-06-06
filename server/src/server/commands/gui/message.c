/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** error
*/

#include "server/command.h"

void packet_message(client_t *client, const char *message)
{
    packet_t *packet = create_packet(message);

    if (!packet)
        return;
    add_packet(client->response, packet);
}
