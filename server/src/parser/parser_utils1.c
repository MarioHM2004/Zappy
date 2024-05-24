/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** parser_utils
*/

#include "parser.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


void handle_port(char *arg, struct argp_state *state, arguments_t *arguments)
{
    (void) state;
    arguments->port = atoi(arg);
}

void handle_width(char *arg, struct argp_state *state, arguments_t *arguments)
{
    (void) state;
    arguments->width = atoi(arg);
}

void handle_height(char *arg, struct argp_state *state, arguments_t *arguments)
{
    (void) state;
    arguments->height = atoi(arg);
}

void handle_name(char *arg, struct argp_state *state, arguments_t *arguments)
{
    arguments->name = calloc(1, sizeof(char *));
    arguments->name[0] = arg;
    for (int i = 1;
        state->argv[state->next] && state->argv[state->next][0] != '-'; i++) {
        arguments->name = realloc(arguments->name, sizeof(char *) * (i + 2));
        arguments->name[i] =
            calloc(strlen(state->argv[state->next]) + 1, sizeof(char));
        arguments->name[i] = state->argv[state->next];
        if (state->argv[state->next + 1] == NULL ||
            state->argv[state->next + 1][0] == '-') {
            arguments->name[i + 1] = NULL;
            break;
        }
        state->next++;
    }
}

void handle_client_nb(char *arg, struct argp_state *state,
    arguments_t *arguments)
{
    (void) state;
    arguments->client_nb = atoi(arg);
}
