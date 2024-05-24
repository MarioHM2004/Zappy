/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** server_loop
*/

#include "server.h"


void run(server_t *server)
{
    while (true) {
        set_fds(server);
        if (select_connection(server) < 0)
            break;
        accept_connection(server);
        handle_packets(server);
        close_connection(server);
    }
}
