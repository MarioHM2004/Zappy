/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** team
*/

#ifndef TEAM_H_
    #define TEAM_H_

    #include "game.h"
    #include "player.h"

    #define GRAPHIC_TEAM_NAME "GRAPHIC"

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


team_t *create_team(const char *name);
team_node_t *create_team_node(team_t *t);
team_list_t *create_team_list(void);
void destroy_team(team_t *t);
void destroy_team_node(team_node_t *tn);
void destroy_team_list(team_list_t *head);

bool add_team(team_list_t *team_list, team_t *team);

uint get_team_list_size(team_list_t *head);
team_t *get_team_by_player(game_t *game, player_t *player);

#endif /* !TEAM_H_ */
