/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** client
*/

#include "server/client.h"
#include "server/packet.h"
#include <stdlib.h>

client_t *create_client(socket_t *socket)
{
    client_t *new_client = calloc(1, sizeof(client_t));

    if (!socket)
        return NULL;
    new_client->socket = socket;
    new_client->request = create_packet_list();
    new_client->response = create_packet_list();
    new_client->type = PENDING;
    if (!new_client->request || !new_client->response) {
        destroy_client(new_client);
        return NULL;
    }
    return new_client;
}

void destroy_client(client_t *c)
{
    if (!c)
        return;
    destroy_socket(c->socket);
    destroy_packet_list(c->request);
    destroy_packet_list(c->response);
    free(c);
}
