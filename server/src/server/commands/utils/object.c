/*
** EPITECH PROJECT, 2024
** utils
** File description:
** object
*/

#include "game/event.h"
#include <stdlib.h>
#include <string.h>

const char *objects[] = {
    "food",
    "linemate",
    "deraumere",
    "sibur",
    "mendiane",
    "phiras",
    "thystame",
    "",
};

object_t *create_object(player_t *player, const char *name)
{
    object_t *object = calloc(1, sizeof(object_t));

    if (!player || !name || !object)
        return NULL;
    for (int i = 0; objects[i][0]; i++) {
        if (strcmp(name, objects[i]) != 0)
            continue;
        object->player = *player;
        strcpy(object->name, name);
        return object;
    }
    return NULL;
}

void destroy_object(object_t *object)
{
    if (!object)
        return;
    free(object);
}

