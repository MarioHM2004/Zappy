/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** event
*/

#ifndef EVENT_H_
#define EVENT_H_


#include <sys/types.h>
#include "game/player.h"

#define MAX_BROADCAST_LENGTH 1024
#define MAX_OBJECT_LENGTH 16

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

typedef struct object_s {
    player_t player;
    char name[MAX_OBJECT_LENGTH];
} object_t;

typedef struct broadcast_s {
    player_t player;
    char text[MAX_BROADCAST_LENGTH];
} broadcast_t;

typedef union {
    player_t player;
    broadcast_t broadcast;
    object_t object;
} event_data_u;

typedef struct event_s {
    event_type_e type;
    event_data_u data;
    size_t size;
} event_t;

typedef struct event_node_s {
    event_t *event;
    float wait_time;
    LIST_ENTRY(event_node_s) entries;
} event_node_t;

typedef struct event_list_s {
    struct event_node_s *lh_first;
} event_list_t;

typedef struct event_func_ptr_s {
    event_type_e type;
    void (*func)(game_t *game, player_t *player, event_t *event);
} event_func_ptr_t;

event_t *create_event(event_type_e type, void *data, size_t size);
event_node_t *create_event_node(event_t *e, float wait_time);
event_list_t *create_event_list(void);
void destroy_event(event_t *e);
void destroy_event_node(event_node_t *en);
void destroy_event_list(event_list_t *head);

// AI
void handle_ai_event(game_t *game, player_t *player, event_t *event);
void forward(game_t *game, player_t *player, event_t *event);
void turn_right(game_t *game, player_t *player, event_t *event);
void turn_left(game_t *game, player_t *player, event_t *event);
void look(game_t *game, player_t *player, event_t *event);
void inventory(game_t *game, player_t *player, event_t *event);
void broadcast(game_t *game, player_t *player, event_t *event);
void connect_nbr(game_t *game, player_t *player, event_t *event);
void fork_player(game_t *game, player_t *player, event_t *event);
void eject(game_t *game, player_t *player, event_t *event);
void take_object(game_t *game, player_t *player, event_t *event);
void set_object(game_t *game, player_t *player, event_t *event);
void incantation(game_t *game, player_t *player, event_t *event);

// utils
object_t *create_object(player_t *player, const char *name);
void destroy_object(object_t *object);
broadcast_t *create_broadcast(player_t *player, const char *text);
void delete_broadcast(broadcast_t *broadcast);
bool add_event(event_list_t *event_list, event_t *event);
uint get_event_list_size(event_list_t *head);

#endif /* !EVENT_H_ */
