/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** game
*/

#ifndef GAME_H_
    #define GAME_H_

    #include <sys/queue.h>
    #include <sys/types.h>
    #include "map.h"
    #include "parser.h"
    #include "server/socket.h"
    #include <stdbool.h>

    #define MAX_TEAM_LENGTH 32
    #define GRAPHIC_NAME "GRAPHIC"

typedef enum {
    NORTH = 1,
    EAST = 2,
    SOUTH = 3,
    WEST = 4
} direction_t;

typedef struct player_s {
    int fd;
    uint number;
    uint x;
    uint y;
    direction_t dir;
    uint level;
    bool alive;
    resources_t *inventory;
} player_t;

typedef struct player_node_s {
    player_t *player;
    LIST_ENTRY(player_node_s) entries;
} player_node_t;

typedef struct player_list_s {
    struct player_node_s *lh_first;
} player_list_t;

typedef struct team_s {
    char name[MAX_TEAM_LENGTH];
    player_list_t *players;
} team_t;

typedef struct team_node_s {
    team_t *team;
    LIST_ENTRY(team_node_s) entries;
} team_node_t;

typedef struct team_list_s {
    struct team_node_s *lh_first;
} team_list_t;

typedef struct game_s {
    bool ended;
    uint freq;
    bool auto_start;
    bool display_eggs;
    team_list_t *teams;
    uint players_per_team;
    map_t *map;
} game_t;

game_t *create_game(arguments_t *arguments);
void set_auto_start(game_t *g, bool auto_start);
void set_display_eggs(game_t *g, bool display_eggs);
void destroy_game(game_t *g);

team_t *create_team(const char *name);
team_node_t *create_team_node(team_t *t);
team_list_t *create_team_list(void);
void destroy_team(team_t *t);
void destroy_team_node(team_node_t *tn);
void destroy_team_list(team_list_t *head);

player_t *create_player(socket_t *socket, uint number);
player_node_t *create_player_node(player_t *p);
player_list_t *create_player_list(void);
void destroy_player(player_t *p);
void destroy_player_node(player_node_t *pn);
void destroy_player_list(player_list_t *head);

#endif /* !GAME_H_ */
