/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** game
*/

#include "game.h"
#include "parser.h"
#include <stdlib.h>

game_t *create_game(arguments_t *arguments)
{
    game_t *game = calloc(1, sizeof(game_t));

    if (!game)
        return NULL;
    //game->map = create_map(arguments->width, arguments->height);
    if (!game->map)
        return NULL;
    game->teams = NULL;
    game->ended = false;
    game->freq = arguments->freq;
    game->players_per_team = arguments->client_nb;
    game->auto_start = arguments->auto_start == 1 ? true : false;
    game->display_eggs = arguments->display_eggs == 0 ? true : false;
    return game;
}