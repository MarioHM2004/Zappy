/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** parser_utils_argp
*/

#include "parser.h"

void handle_argp_key_end(char *arg, struct argp_state *state,
    arguments_t *args)
{
    if (args->port == 0 || args->width == 0 || args->height == 0
        || (!args->name || !args->name[0]) || args->client_nb == 0 ||
        args->freq == 0 || args->auto_start == -1 || args->display_eggs == -1)
        argp_usage(state);
}

void handle_key_arg(char *arg, struct argp_state *state,
    arguments_t *arguments)
{
    (void) arg;
    (void) state;
    (void) arguments;
    return;
}
