/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** parser
*/

#include "parser.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

const char *argp_program_version = "Zappy 1.0";
const char *argp_program_bug_address = "oriol.linan@epitech.eu";

/* Program documentation. */
static char doc[] = "A server, created in C, that generates the inhabitants' world.";

/* The options we understand. */
static struct argp_option options[] = {
    {"port", 'p', "NUM", 0, "Port number"},
    {"width", 'x', "NUM", 0, "Width of the world"},
    {"height", 'y', "NUM", 0, "Height of the world"},
    {"name", 'n', "NAME", 0, "Names of the teams"},
    {"clientNb", 'c', "NUM", 0, "Number of authorized clients per team"},
    {"freq", 'f', "NUM", 0, "Reciprocal of time unit for execution of actions"},
    {"auto-start", 'a', "on|off", 0, "Does the greeting is sent automatically"},
    {"display-eggs", 'd', "true|false", 0, "Eggs are visible and destructible"},
    {"verbose", 'v', "verbose", 0, "Produce verbose output"},
    {0}
};

static bool check_error(arguments_t *arguments)
{
    if (arguments->port == 0 || arguments->width == 0 || arguments->height == 0 ||
        (!arguments->name || !arguments->name[0]) || arguments->clientNb == 0 || arguments->freq == 0
        || arguments->auto_start == -1 || arguments->display_eggs == -1)
        return true;
    return false;

}

/* Parse a single option. */
static error_t parse_opt(int key, char *arg, struct argp_state *state) {
    /* Get the input argument from argp_parse, which we
       know is a pointer to our arguments structure. */
    arguments_t *arguments = state->input;

    switch (key) {
        case 'p':
            arguments->port = atoi(arg);
            break;
        case 'x':
            arguments->width = atoi(arg);
            break;
        case 'y':
            arguments->height = atoi(arg);
            break;
        case 'n':
            arguments->name = calloc(1, sizeof(char *));
            arguments->name[0] = arg;
            for (int i = 0; state->argv[state->next] &&  state->argv[state->next][0] != '-'; i++) {
                printf ("state->argv[state->next] = %s\n", state->argv[state->next]);
                arguments->name = realloc(arguments->name, sizeof(char *) * (i + 2));
                arguments->name[i] = calloc(strlen(state->argv[state->next]) + 1, sizeof(char));
                arguments->name[i] = state->argv[state->next];
                if (state->argv[state->next + 1] == NULL ||
                    state->argv[state->next + 1][0] == '-') {
                    arguments->name[i + 1] = NULL;
                    break;
                }
                state->next++;
            }
            break;
        case 'c':
            arguments->clientNb = atoi(arg);
            break;
        case 'f':
            arguments->freq = atoi(arg);
            break;
        case 'a':
            if (strcmp(arg, "on") == 0)
                arguments->auto_start = ON;
            else if (strcmp(arg, "off") == 0)
                arguments->auto_start = OFF;
            break;
        case 'd':
            if (strcmp(arg, "true") == 0)
                arguments->display_eggs = TRUE;
            else if (strcmp(arg, "false") == 0)
                arguments->display_eggs = FALSE;
            break;
        case 'v':
            arguments->verbose = true;
            break;
        case ARGP_KEY_ARG:
            break;

        case ARGP_KEY_END:
            if (check_error(arguments))
                argp_usage(state);
            break;
        default:
            return ARGP_ERR_UNKNOWN;
    }
    return 0;
}

/* Our argp parser. */
static struct argp argp = {options, parse_opt, 0, doc};

arguments_t parser(int argc, char **argv)
{
    arguments_t arguments;

    arguments.port = 0;
    arguments.width = 0;
    arguments.height = 0;
    arguments.clientNb = 0;
    arguments.freq = 0;
    arguments.verbose = false;
    arguments.auto_start = -1;
    arguments.display_eggs = -1;

    /* Parse our arguments; every option seen by parse_opt will
       be reflected in arguments. */
    argp_parse(&argp, argc, argv, 0, 0, &arguments);

    return (arguments);
}
