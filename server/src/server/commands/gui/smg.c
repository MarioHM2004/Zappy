/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** smg
*/

#include "libs/lib.h"
#include "server/command.h"
#include "game/player.h"

void smg_command(server_t *server, client_t *client, char *msg)
{
    packet_t *packet = NULL;
    char *response = formatstr(SMG_RESPONSE, msg);

    if (!response)
        return packet_message(client, ERROR_MESSAGE);
    packet = create_packet(response);
    free(response);
    if (!packet)
        return packet_message(client, ERROR_MESSAGE);
    add_packet(client->response, packet);
}
