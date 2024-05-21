/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** client
*/

#ifndef CLIENT_H_
#define CLIENT_H_

#include <sys/queue.h>
#include "socket.h"
#include "game.h"

typedef struct client_node_s {
    socket_t *socket;
    LIST_ENTRY(client_node_s) entries;
} client_node_t;

typedef struct client_list_s {
    struct client_node_s *lh_first;
} client_list_t;

#endif /* !CLIENT_H_ */
