/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** server
*/

#ifndef SERVER_H_
    #define SERVER_H_

    #include <sys/types.h>
    #include "packet.h"
    #include "parser.h"
    #include "server/action.h"
    #include "socket.h"
    #include "client.h"
    #include "game/game.h"

    #define CRLF "\n"
    #define MAX(a, b) ((a) >= (b) ? (a) : (b))
    #define MIN(a, b) ((a) <= (b) ? (a) : (b))
    #define MAX_CLIENTS 1024

typedef struct server_s {
    socket_t *socket;
    client_list_t *clients;
    game_t *game;
    action_list_t *actions;
    fd_set read_fds;
    fd_set write_fds;
    fd_set except_fds;
} server_t;

server_t *create_server(arguments_t *arguments);
void destroy_server(server_t *s);
void run(server_t *server);
void set_fds(server_t *server);
int select_connection(server_t *server, struct timeval *timeout);
void accept_connection(server_t *server);
void close_connection(server_t *server);
void handle_packets(server_t *server);
void process_client_packets(server_t *server, client_t *client);
void write_packets(socket_t *socket, packet_list_t **packets);
bool read_packets(socket_t *socket, packet_list_t *packets);

#endif /* !SERVER_H_ */
