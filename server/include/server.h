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


typedef struct server_s {
    socket_t *socket;
    client_list_t *clients;
    gui_t *gui;
    game_t *game;
} server_t;

server_t *create_server(arguments_t *arguments);
void destroy_server(server_t *s);

#endif /* !SERVER_H_ */
