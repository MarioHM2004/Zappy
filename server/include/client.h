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
#include "packet.h"

typedef struct client_s {
    socket_t *socket;
    packet_list_t *packets;
} client_t;

typedef struct client_node_s {
    client_t *client;
    LIST_ENTRY(client_node_s) entries;
} client_node_t;

typedef struct client_list_s {
    struct client_node_s *lh_first;
} client_list_t;

client_t *create_client(socket_t *socket);
client_node_t *create_client_node(client_t *c);
client_list_t *create_client_list(void);
void destroy_client(client_t *c);
void destroy_client_node(client_node_t *cn);
void destroy_client_list(client_list_t *head);

#endif /* !CLIENT_H_ */
