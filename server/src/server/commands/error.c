/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** error
*/

#include "server/command.h"

void packet_error(client_t *client)
{
    packet_t *packet = create_packet(ERROR_RESPONSE);

    if (!packet)
        return;
    add_packet(client->response, packet);
}
