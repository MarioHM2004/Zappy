/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** parser
*/

#include "libs/log.h"
#include "parser.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

const char *argp_program_version = "Zappy 1.0";
const char *argp_program_bug_address = "oriol.linan@epitech.eu";

/* Program documentation. */
static const char doc[] = "Zappy server made in C.";

static struct argp_option options[] = {
    {"port", 'p', "NUM", 0, "Port number"},
    {"width", 'x', "NUM", 0, "Width of the world"},
    {"height", 'y', "NUM", 0, "Height of the world"},
    {"name", 'n', "NAME", 0, "Names of the teams"},
    {"clientNb", 'c', "NUM", 0, "Number of authorized clients per team"},
    {"freq", 'f', "NUM", 0, "Time unit for execution of actions"},
    {"auto-start", 'a', "on|off", 0, "Greeting is sent automatically"},
    {"display-eggs", 'd', "true|false", 0, "Eggs are visible & destructible"},
    {"verbose", 'v', "verbose", 0, "Produce verbose output"},
    {0}
};

static const parser_ptr_t parser_ptr[] = {
    {'p', handle_port},
    {'x', handle_width},
    {'y', handle_height},
    {'n', handle_name},
    {'c', handle_client_nb},
    {'f', handle_freq},
    {'a', handle_auto_start},
    {'d', handle_display_eggs},
    {'v', handle_verbose},
    {ARGP_KEY_ARG, handle_key_arg},
    {ARGP_KEY_END, handle_argp_key_end},
    {0, NULL}
};

/* Lookup function for parser_ptr array */
static void (*get_fnc_ptr(int key))(char *, struct argp_state *, arguments_t *)
{
    for (int i = 0; parser_ptr[i].fnc_ptr != NULL; i++) {
        if (parser_ptr[i].key == key) {
            return parser_ptr[i].fnc_ptr;
        }
    }
    return NULL;
}

/* Parse a single option. */
static error_t parse_opt(int key, char *arg, struct argp_state *state)
{
    arguments_t *arguments = state->input;
    void (*fnc_ptr)(char *, struct argp_state *, arguments_t *)
        = get_fnc_ptr(key);

    if (fnc_ptr)
        fnc_ptr(arg, state, arguments);
    else
        return ARGP_ERR_UNKNOWN;
    return 0;
}

static void log_arguments(arguments_t *arguments)
{
    log_info("Port: %d", arguments->port);
    log_info("Width: %d", arguments->width);
    log_info("Height: %d", arguments->height);
    log_info("ClientNb: %d", arguments->client_nb);
    for (int i = 0; arguments->name[i]; i++) {
        log_info("Name: %s", arguments->name[i]);
    }
    log_info("Freq: %d", arguments->freq);
    log_info("Auto-start: %s",
        arguments->auto_start == 1 ? "OFF" : "ON");
    log_info("Display-eggs: %s",
        arguments->display_eggs == 0 ? "FALSE" : "TRUE");
    log_info("Verbose: %d", arguments->verbose);
}

arguments_t *parser(int argc, char **argv)
{
    arguments_t *arguments = calloc(1, sizeof(arguments_t));
    struct argp argp = {options, parse_opt, 0, doc};

    if (!arguments)
        return NULL;
    arguments->port = 0;
    arguments->width = 0;
    arguments->height = 0;
    arguments->client_nb = 0;
    arguments->freq = 0;
    arguments->verbose = false;
    arguments->auto_start = -1;
    arguments->display_eggs = -1;
    argp_parse(&argp, argc, argv, 0, 0, arguments);
    log_arguments(arguments);
    return arguments;
}

void free_arguments(arguments_t *arguments)
{
    if (!arguments)
        return;
    if (arguments->name) {
        for (int i = 0; arguments->name[i]; i++) {
            free(arguments->name[i]);
        }
        free(arguments->name);
    }
    free(arguments);
}
