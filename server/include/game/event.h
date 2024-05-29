/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** event
*/

#ifndef EVENT_H_
#define EVENT_H_

#include "game.h"

#define MAX_BROADCAST_LENGTH 1024

typedef enum {
    FORWARD,
    TURN_RIGHT,
    TURN_LEFT,
    LOOK,
    INVENTORY,
    BROADCAST,
    CONNECT_NBR,
    FORK,
    EJECT,
    TAKE_OBJECT,
    SET_OBJECT,
    START_INCANTATION
} event_type_e;

typedef struct broadcast_s {
    player_t player;
    char message[MAX_BROADCAST_LENGTH];
} broadcast_t;

typedef union {
    player_t player;
    broadcast_t broadcast;
} event_data_u;

typedef struct event_s {
    event_type_e type;
    event_data_u data;
    size_t size;
} event_t;

typedef struct event_node_s {
    event_t *event;
    LIST_ENTRY(event_node_s) entries;
} event_node_t;

typedef struct event_list_s {
    struct event_node_s *lh_first;
} event_list_t;

event_t *create_event(event_type_e type, void *data, size_t size);
event_node_t *create_event_node(event_t *e);
event_list_t *create_event_list(void);
void destroy_event(event_t *e);
void destroy_event_node(event_node_t *en);
void destroy_event_list(event_list_t *head);


#endif /* !EVENT_H_ */
