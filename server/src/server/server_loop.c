/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** server_loop
*/

#include "game/game.h"
#include "server/server.h"

void run(server_t *server)
{
    struct timeval timeout = { .tv_sec = 0, .tv_usec = 100 };

    while (true) {
        set_fds(server);
        if (select_connection(server, &timeout) < 0)
            break;
        accept_connection(server);
        handle_packets(server);
        game_tick(server->game);
        close_connection(server);
    }
}
