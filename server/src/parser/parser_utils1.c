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

static void free_arguments_name(arguments_t *arguments)
{
    for (int i = 0; arguments->name[i]; i++) {
        free(arguments->name[i]);
    }
    free(arguments->name);
}

static int allocate_initial_name(char *arg, arguments_t *arguments) {
    arguments->name = calloc(2, sizeof(char *));
    if (!arguments->name)
        return -1;
    arguments->name[0] = strdup(arg);
    if (!arguments->name[0]) {
        free(arguments->name);
        return -1;
    }
    arguments->name[1] = NULL;
    return 0;
}

static void append_additional_names(struct argp_state *state, arguments_t *arguments)
{
    int name_count = 1;
    char **temp = NULL;

    while (state->argv[state->next] && state->argv[state->next][0] != '-') {
        name_count++;
        temp = realloc(arguments->name, sizeof(char *) * (name_count + 1));
        if (!temp)
            return;
        arguments->name = temp;
        arguments->name[name_count - 1] = strdup(state->argv[state->next]);
        if (!arguments->name[name_count - 1])
            return;
        if (state->argv[state->next + 1] == NULL ||
            state->argv[state->next + 1][0] == '-')
            break;
        state->next++;
    }
    arguments->name[name_count] = NULL;
}

void handle_name(char *arg, struct argp_state *state, arguments_t *arguments)
{
    if (allocate_initial_name(arg, arguments) != 0)
        return;
    append_additional_names(state, arguments);
}

void handle_client_nb(char *arg, struct argp_state *state,
    arguments_t *arguments)
{
    (void) state;
    arguments->client_nb = atoi(arg);
}
