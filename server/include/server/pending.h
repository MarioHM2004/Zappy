/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** pending
*/

#ifndef PENDING_H_
#define PENDING_H_

#include "socket.h"
#include "packet.h"

typedef struct pending_s {
    socket_t *socket;
    packet_list_t *request;
    packet_list_t *response;
} pending_t;

typedef struct pending_node_s {
    pending_t *pending;
    LIST_ENTRY(pending_node_s) entries;
} pending_node_t;

typedef struct pending_list_s {
    struct pending_node_s *lh_first;
} pending_list_t;

pending_t *create_pending(socket_t *socket);
pending_node_t *create_pending_node(pending_t *pending);
pending_list_t *create_pending_list(void);
void destroy_pending(pending_t *pending);
void destroy_pending_node(pending_node_t *node);
void destroy_pending_list(pending_list_t *list);

#endif /* !PENDING_H_ */
