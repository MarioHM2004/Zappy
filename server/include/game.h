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

#define MAX_TEAM_LENGTH 32
#define GRAPHIC_NAME "GRAPHIC"

enum direction_e {
    NORTH = 1,
    EAST = 2,
    SOUTH = 3,
    WEST = 4
};

typedef struct player_s {
    int fd;
    uint number;
    uint x;
    uint y;
    direction_e dir;
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

#endif /* !GAME_H_ */
