/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** server
*/

#include "server.h"
#include <netinet/in.h>
#include <stdlib.h>

server_t *create_server(arguments_t *arguments)
{
    server_t *server = calloc(1, sizeof(server_t));

    if (!server)
        return NULL;
    //server->socket = create_socket(arguments->port, INADDR_ANY);
    if (!server->socket)
        return NULL;
    server->clients = NULL;
    server->gui = NULL;
    server->game = NULL;
    return server;
}