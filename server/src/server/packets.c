/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** packets
*/

#include "server.h"

static void handle_client_packets(server_t *server)
{
    (void)server;
    return;
}

static void handle_gui_packets(server_t *server)
{
    (void)server;
    return;
}

static void handle_pending_packets(server_t *server)
{
    pending_node_t *tmp = NULL;

    if (!server->pending)
        return;
    LIST_FOREACH(tmp, server->pending, entries) {
    }
    return;
}

void handle_packets(server_t *server)
{
    handle_pending_packets(server);
}
