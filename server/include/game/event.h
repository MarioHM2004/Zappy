/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** event
*/

#ifndef EVENT_H_
#define EVENT_H_

#include "game.h"
#include "server/client.h"
#include <stddef.h>

#define MAX_BROADCAST_LENGTH 1024

typedef enum {
    // AI Protocol
    FORWARD,
    TURN_RIGHT,
    TURN_LEFT,
    LOOK,
    INVENTORY,
    BROADCAST_REQUEST,
    CONNECT_NBR,
    FORK,
    EJECT,
    DEATH,
    TAKE_OBJECT,
    SET_OBJECT,
    START_INCANTATION_REQUEST,

    // GUI Protocol
    NEW_CLIENT,
    EXPULSION,
    BROADCAST_MESSAGE,
    START_INCANTATION_ACTION,
    END_INCANTATION_ACTION,
    EGG_LAYED,
    RESOURCE_DROPPED,
    RESOURCE_COLLECTED,
    PLAYER_DEATH,
    EGG_HATCHED,
} event_type_e;

typedef struct new_client_s {
    client_t client;
    player_t player;
} new_client_t;

typedef struct broadcast_request_s {
    int fd;
    char text[MAX_BROADCAST_LENGTH];
} broadcast_request_t;

typedef struct broadcast_message_s {
    player_t player;
    char text[MAX_BROADCAST_LENGTH];
} broadcast_message_t;

typedef struct start_incantation_action_s {
    player_t player;
    team_t team;
} start_incantation_action_t;

typedef struct end_incantation_action_s {
    player_t player;
    bool success;
} end_incantation_action_t;

typedef struct resource_action_s {
    player_t player;
    int i;
} resource_action_t;

typedef union {
    int fd;
    new_client_t new_client;
    player_t player;
    broadcast_request_t broadcast_request;
    broadcast_message_t broadcast_message;
    start_incantation_action_t start_incantation_action;
    end_incantation_action_t end_incantation_action;
    resource_action_t resource_action;
} event_data_u;

typedef struct event_s {
    event_type_e type;
    event_data_u data;
    size_t size;
} event_t;

#endif /* !EVENT_H_ */
