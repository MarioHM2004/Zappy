/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** game
*/

#include "game.h"
#include <stdlib.h>

game_t *create_game(map_t *map, team_list_t *teams, uint players_per_team, uint freq)
{
    game_t *game = calloc(1, sizeof(game_t));

    game->ended = false;
    game->freq = freq;
    //game->auto_start = auto
    return game;

}