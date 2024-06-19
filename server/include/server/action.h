/*
** EPITECH PROJECT, 2024
** server
** File description:
** action
*/

#ifndef ACTION_H_
#define ACTION_H_

#include "game/event.h"
#include "game/player.h"
#include <sys/queue.h>

typedef enum {
    // response goes to -> AI
    EVENT_COMPLETED, // AI event is completed
    // response goes to -> GUI
    NEW_GUI, // new GUI connection
    NEW_PLAYER, // new AI connection
    PLAYER_MOVED, // AI forward, left, right, or eject
    PLAYER_EJECT, // AI eject action
    PLAYER_INVENTORY, // AI set, take or lost food
    PLAYER_SET, // AI set command
    PLAYER_TAKE, // AI take command
    PLAYER_BROADCAST, // AI broadcast action
    PLAYER_FORK, // AI layes an egg
    PLAYER_DEAD, // AI dies or disconnects
    INCANTATION_START, // AI starts incantation by first player
    INCANTATION_END, // AI incantation ended
    INCANTATION_COMPLETE, // AI succesfully incantate
    EGG_LAYED, // AI fork action ended
    EGG_MATURED, // AI egg matured
    MAP_REFILL, // map is refilled
} action_type_e;

typedef struct event_completed_s {
    event_type_e type;
    char *response;
    bool successful;
} event_completed_t;

typedef union {
    event_completed_t event_completed;
    client_t *client;
    player_t *player;
    object_t object;
    broadcast_t broadcast;
    player_list_t *players;
    map_t *map;
} action_data_u;

typedef struct action_s {
    action_type_e type;
    action_data_u data;
    size_t size;
} action_t;

typedef struct action_node_s {
    action_t *action;
    LIST_ENTRY(action_node_s) entries;
} action_node_t;

typedef struct action_list_s {
    struct action_node_s *lh_first;
} action_list_t;

typedef void (*action_assign_f)(action_t *, void *);
typedef void (*action_response_f)(server_t *, action_t *);

typedef struct action_assign_s {
    action_type_e type;
    action_assign_f func;
} action_assign_t;

typedef struct action_response_s {
    action_type_e type;
    action_response_f func;
} action_response_t;

action_t *create_action(action_type_e type, void *data, size_t size);
action_node_t *create_action_node(action_t *a);
action_list_t *create_action_list(void);

void destroy_action(action_t *a);
void destroy_action_node(action_node_t *an);
void destroy_action_list(action_list_t *head);

void add_action(action_list_t *head, action_t *action);

#endif // !ACTION_H_

