/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** server
*/

#include "server/server.h"
#include "parser.h"
#include "server/client.h"
#include "server/socket.h"
#include <netinet/in.h>
#include <stdlib.h>

server_t *create_server(arguments_t *arguments)
{
    server_t *server = calloc(1, sizeof(server_t));

    if (!server)
        return NULL;
    server->socket = create_socket(arguments->port, INADDR_ANY);
    server->clients = create_client_list();
    server->game = create_game(arguments);
    free_arguments(arguments);
    if (!server->socket || !server->clients || !server->game) {
        destroy_server(server);
        return NULL;
    }
    return server;
}

void destroy_server(server_t *server)
{
    if (!server)
        return;
    destroy_socket(server->socket);
    destroy_client_list(server->clients);
    // destroy_game(server->game);
    free(server);
}
