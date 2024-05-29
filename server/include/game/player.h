/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** player
*/


#ifndef PLAYER_H_
    #define PLAYER_H_

    #include "game.h"
    #include "server/socket.h"

typedef struct event_list_s event_list_t;
typedef struct event_s event_t;

typedef struct player_s {
    int fd;
    uint number;
    uint level;
    position_t pos;
    direction_e dir;
    player_state_e state;
    resources_t *inventory;
    event_list_t *events;
} player_t;

typedef struct player_node_s {
    player_t *player;
    LIST_ENTRY(player_node_s) entries;
} player_node_t;

typedef struct player_list_s {
    struct player_node_s *lh_first;
} player_list_t;

player_t *create_player(socket_t *socket, uint number, uint x, uint y);
player_node_t *create_player_node(player_t *p);
player_list_t *create_player_list(void);
void destroy_player(player_t *p);
void destroy_player_node(player_node_t *pn);
void destroy_player_list(player_list_t *head);

bool append_event_to_player(event_t *event, player_t *player);

#endif /* !PLAYER_H_ */
