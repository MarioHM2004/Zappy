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
    #include "parser.h"

    #define MAX_TEAM_LENGTH 32

typedef struct server_s server_t;

typedef enum {
    EGG,
    ALIVE,
    DEAD
} player_state_e;

typedef struct position_s {
    int x;
    int y;
} position_t;

typedef struct team_list_s team_list_t;
typedef struct player_list_s player_list_t;
typedef struct map_s map_t;

typedef struct game_s {
    bool ended;
    uint freq;
    bool auto_start;
    bool display_eggs;
    team_list_t *teams;
    player_list_t *players;
    uint players_per_team;
    map_t *map;
} game_t;

game_t *create_game(arguments_t *arguments);
void set_auto_start(game_t *g, bool auto_start);
void set_display_eggs(game_t *g, bool display_eggs);
void destroy_game(game_t *g);
void game_tick(server_t *server);

#endif /* !GAME_H_ */
