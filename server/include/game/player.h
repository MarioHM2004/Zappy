/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** player
*/


#ifndef PLAYER_H_
    #define PLAYER_H_

    #include "game.h"
    #include "game/map.h"
    #include "game/resources.h"
#include "server/client.h"
    #include "server/socket.h"
    #include <sys/types.h>

    #define MAX_LEVEL 8

typedef struct event_list_s event_list_t;
typedef struct event_s event_t;

typedef struct incantation_s {
    uint level;
    uint players;
    uint linemate;
    uint deraumere;
    uint sibur;
    uint mendiane;
    uint phiras;
    uint thystame;
} incantation_t;

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

player_t *assign_player(socket_t *socket, server_t *server, char *team_name);
player_t *create_egg(map_t *map, position_t pos);
player_t *spawn_egg(map_t *map);
player_node_t *create_player_node(player_t *p);
player_list_t *create_player_list(void);
void destroy_player(player_t *p);
void destroy_player_node(player_node_t *pn);
void destroy_player_list(player_list_t *head);
void remove_player(game_t *game, player_t *player);

bool add_player(player_list_t *player_list, player_t *player);

uint get_player_list_size(player_list_t *head);
bool is_player_in_list(player_list_t *head, player_t *player);
player_t *get_player_by_fd(player_list_t *players, int fd);

void player_tick(game_t *game, player_t *player);
bool move_player(map_t *map,player_t *player, position_t new_pos);
void log_player(player_t *player);
bool add_response_to_player(client_list_t *client_list, player_t *player
    , char *response);
#endif /* !PLAYER_H_ */
