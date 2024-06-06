/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** game
*/

#include "game/map.h"
#include "game/player.h"
#include "game/team.h"
#include "libs/log.h"
#include "server/server.h"
#include <stdlib.h>
#include <time.h>

game_t *create_game(arguments_t *arguments)
{
    game_t *game = calloc(1, sizeof(game_t));

    if (!game)
        return NULL;
    game->map = create_map(arguments->width, arguments->height);
    if (!game->map)
        return NULL;
    game->teams = init_teams(arguments->name);
    game->players = create_player_list();
    game->ended = false;
    game->freq = arguments->freq;
    game->players_per_team = arguments->client_nb;
    game->auto_start = arguments->auto_start == 1 ? true : false;
    game->display_eggs = arguments->display_eggs == 0 ? true : false;
    return game;
}

void destroy_game(game_t *game)
{
    destroy_team_list(game->teams);
    destroy_map(game->map);
}

static bool valid_tick() {
    static clock_t last_time = 0;
    clock_t elapsed_time = clock();
    clock_t diff = elapsed_time - last_time;

    if (diff >= CLOCKS_PER_SEC) {
        log_info("tick={%d}", elapsed_time / CLOCKS_PER_SEC);
        last_time = elapsed_time;
        return true;
    }
    return false;
}

void game_tick(server_t *server)
{
    team_node_t *team_node = NULL;
    player_node_t *player_node = NULL;

    if (!valid_tick())
        return;
    LIST_FOREACH(team_node, server->game->teams, entries) {
        LIST_FOREACH(player_node, team_node->team->players, entries)
            player_tick(server->game, player_node->player);
    }
}

