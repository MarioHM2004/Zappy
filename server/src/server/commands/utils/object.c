/*
** EPITECH PROJECT, 2024
** utils
** File description:
** object
*/

#include "game/event.h"
#include "game/resources.h"
#include <stdlib.h>
#include <string.h>

const string_to_resource_t objects[] = {
    { "food", FOOD },
    { "linemate", LINEMATE },
    { "deraumere", DERAUMERE },
    { "sibur", SIBUR },
    { "mendiane", MENDIANE },
    { "phiras", PHIRAS },
    { "thystame", THYSTAME },
};

object_t *create_object(player_t *player, const char *name)
{
    object_t *object = calloc(1, sizeof(object_t));
    size_t len = sizeof(objects) / sizeof(objects[0]);

    if (!player || !name || !object)
        return NULL;
    for (size_t i = 0; i < len; i++) {
        if (strcmp(name, objects[i].name) != 0)
            continue;
        object->player = player;
        object->resource = objects[i].resource;
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

