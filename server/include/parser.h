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

typedef enum { FALSE, TRUE } bool_e;
typedef enum { ON, OFF } switch_e;


typedef struct {
    int port;
    int width;
    int height;
    int clientNb;
    int freq;
    bool verbose;
    char **name; // Adjust size as needed
    switch_e auto_start;
    bool_e display_eggs;
} arguments_t;

arguments_t parser(int argc, char **argv);

#endif /* !PARSER_H_ */