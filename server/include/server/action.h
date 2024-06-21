/*
** EPITECH PROJECT, 2024
** server
** File description:
** action
*/

#ifndef ACTION_H_
#define ACTION_H_

#include "game/event.h"
#include "game/game.h"
#include "game/player.h"
#include "game/resources.h"
#include <sys/queue.h>

typedef enum {
    // response goes to -> AI
    EVENT_COMPLETED, // AI event is completed
    EVENT_RECEIVED, // AI event is received
    // response goes to -> GUI
    NEW_GUI,
    NEW_PLAYER,
    PLAYER_EJECT,
    PLAYER_INVENTORY,
    PLAYER_SET,
    PLAYER_TAKE,
    PLAYER_BROADCAST,
    PLAYER_FORK,
    PLAYER_DEAD,
    INCANTATION_START,
    INCANTATION_END,
    INCANTATION_COMPLETE,
    EGG_LAYED,
    EGG_DEATH,
    EGG_MATURED,
    MAP_REFILL,
} action_type_e;

typedef struct event_completed_s {
    event_type_e type;
    player_t *player;
    char *response;
    bool successful;
} event_completed_t;

typedef struct event_received_s {
    event_received_type_e type;
    player_t *player;
    char *response;
    bool successful;
} event_received_t;

typedef struct egg_shell_s {
    player_t *player;
    player_t *egg;
} egg_shell_t;

typedef enum {
    FAILED,
    SUCCESSFUL,
    IN_PROGRESS,
} incantation_state_e;

typedef struct incantation_action_s {
    player_list_t *players;
    incantation_state_e state;
} incantation_action_t;

typedef union {
    event_completed_t event_completed;
    event_received_t event_received;
    client_t *client;
    player_t *player;
    object_t object;
    broadcast_t broadcast;
    incantation_action_t incantation;
    egg_shell_t egg_shell;
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
typedef void (*action_event_f)(server_t *, action_t *);

typedef struct action_assign_s {
    action_type_e type;
    action_assign_f func;
} action_assign_t;

typedef struct action_response_s {
    action_type_e type;
    action_response_f func;
} action_response_t;

typedef struct action_event_s {
    event_type_e type;
    action_event_f func;
} action_event_t;

action_t *create_action(action_type_e type, void *data, size_t size);
action_node_t *create_action_node(action_t *a);
action_list_t *create_action_list(void);


void destroy_action(action_t *a);
void destroy_action_node(action_node_t *an);
void destroy_action_list(action_list_t *head);

void add_action(action_list_t *head, action_t *action);

void process_actions(server_t *server);
// action responses
void event_completed(server_t *server, action_t *action);
void event_received(server_t *server, action_t *action);
void new_gui(server_t *server, action_t *action);
void new_player(server_t *server, action_t *action);
void player_moved(server_t *server, action_t *action);
void player_eject(server_t *server, action_t *action);
void player_inventory(server_t *server, action_t *action);
void player_set(server_t *server, action_t *action);
void player_take(server_t *server, action_t *action);
void player_broadcast(server_t *server, action_t *action);
void player_fork(server_t *server, action_t *action);
void player_dead(server_t *server, action_t *action);
void incantation_start(server_t *server, action_t *action);
void incantation_end(server_t *server, action_t *action);
void incantation_complete(server_t *server, action_t *action);
void egg_layed(server_t *server, action_t *action);
void egg_matured(server_t *server, action_t *action);
void egg_death(server_t *server, action_t *action);
void map_refill(server_t *server, action_t *action);

action_t *create_event_completed_action(player_t *player,
    event_type_e event_type, char *response, bool successful);
action_t *create_event_received_action(player_t *player,
    event_received_type_e event_type, char *response, bool successful);

#endif // !ACTION_H_

