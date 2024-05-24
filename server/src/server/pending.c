/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** pending
*/

#include "pending.h"
#include <stdlib.h>

pending_t *create_pending(socket_t *socket)
{
    pending_t *pending = calloc(1, sizeof(pending_t));

    if (!pending)
        return NULL;
    pending->socket = socket;
    pending->packets = create_packet_list();
    if (!pending->packets) {
        free(pending);
        return NULL;
    }
    return pending;
}

void destroy_pending(pending_t *pending)
{
    if (!pending)
        return;
    destroy_socket(pending->socket);
    destroy_packet_list(pending->packets);
    free(pending);
}
