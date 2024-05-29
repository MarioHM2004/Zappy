/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** command
*/

#ifndef COMMAND_H_
#define COMMAND_H_

#include "server.h"

#define MAX_COMMAND_NAME_LENGTH 64

typedef void (*client_command_func_t)(server_t *, client_t *, char *);

typedef struct client_command_s {
    char name[MAX_COMMAND_NAME_LENGTH];
    client_command_func_t func;
} client_command_t;

#endif /* !COMMAND_H_ */
