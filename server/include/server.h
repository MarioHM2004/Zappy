/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** server
*/

#ifndef SERVER_H_
#define SERVER_H_

#include <sys/types.h>
#include "gui.h"
#include "parser.h"
#include "socket.h"
#include "client.h"
#include "game.h"
#include "pending.h"

#define MAX(a, b) ((a) >= (b) ? (a) : (b))
#define MIN(a, b) ((a) <= (b) ? (a) : (b))

typedef struct server_s {
    socket_t *socket;
    client_list_t *clients;
    gui_list_t *guis;
    pending_list_t *pending;
    game_t *game;
    fd_set read_fds;
    fd_set write_fds;
    fd_set except_fds;
} server_t;

server_t *create_server(arguments_t arguments);
void destroy_server(server_t *s);
void run(server_t *server);
void set_fds(server_t *server);
int select_connection(server_t *server);
void accept_connection(server_t *server);
void close_connection(server_t *server);
void handle_packets(server_t *server);

#endif /* !SERVER_H_ */
