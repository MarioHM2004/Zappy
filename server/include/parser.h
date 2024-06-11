/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** parser
*/

#ifndef PARSER_H_
    #define PARSER_H_

    #include <argp.h>
    #include <stdbool.h>


typedef enum {
    FALSE,
    TRUE
} bool_t;

typedef enum {
    ON,
    OFF
} switch_t;

typedef struct {
    int port;
    int width;
    int height;
    int client_nb;
    int freq;
    bool verbose;
    char **name; // Adjust size as needed
    switch_t auto_start;
    bool_t display_eggs;
} arguments_t;

typedef struct {
    int key;
    void (*fnc_ptr)(char *arg, struct argp_state *state,
        arguments_t *arguments);
} parser_ptr_t;

arguments_t *parser(int argc, char **argv);
void handle_port(char *arg, struct argp_state *state, arguments_t *arguments);
void handle_width(char *arg, struct argp_state *state, arguments_t *arguments);
void handle_height(char *arg, struct argp_state *state
    , arguments_t *arguments);
void handle_name(char *arg, struct argp_state *state, arguments_t *arguments);
void handle_client_nb(char *arg, struct argp_state *state
    , arguments_t *arguments);
void handle_freq(char *arg, struct argp_state *state, arguments_t *arguments);
void handle_auto_start(char *arg, struct argp_state *state
    , arguments_t *arguments);
void handle_display_eggs(char *arg, struct argp_state *state
    , arguments_t *arguments);
void handle_verbose(char *arg, struct argp_state *state
    , arguments_t *arguments);
void handle_key_arg(char *arg, struct argp_state *state
    , arguments_t *arguments);
void handle_argp_key_end(char *arg, struct argp_state *state
    , arguments_t *arguments);
void free_arguments(arguments_t *arguments);

#endif /* !PARSER_H_ */
