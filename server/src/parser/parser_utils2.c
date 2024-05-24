/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** parser_utils2
*/
#include "parser.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


void handle_freq(char *arg, struct argp_state *state, arguments_t *arguments)
{
    (void) state;
    arguments->freq = atoi(arg);
}

void handle_auto_start(char *arg, struct argp_state *state,
    arguments_t *arguments)
{
    (void) state;
    if (strcmp(arg, "on") == 0)
        arguments->auto_start = ON;
    else if (strcmp(arg, "off") == 0)
        arguments->auto_start = OFF;
}

void handle_display_eggs(char *arg, struct argp_state *state,
    arguments_t *arguments)
{
    (void) state;
    if (strcmp(arg, "true") == 0)
        arguments->display_eggs = TRUE;
    else if (strcmp(arg, "false") == 0)
        arguments->display_eggs = FALSE;
}

void handle_verbose(char *arg, struct argp_state *state,
    arguments_t *arguments)
{
    arguments->verbose = true;
}
