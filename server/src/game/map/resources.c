/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** resources
*/

#include "game/resources.h"
#include "game/game.h"
#include "game/map.h"
#include <stdbool.h>
#include <stdlib.h>

static uint resources_quantity(float density, uint width, uint height)
{
    int quantity = ((width * height) * density);

    if (quantity < 1)
        return 1;
    return (uint)quantity;
}

static position_t *random_positions(map_t *map, uint quantity, uint width, uint height)
{
    position_t *random_position = calloc(quantity + 1, sizeof(position_t *));

    if (!random_position)
        return NULL;

    for (uint i = 0; i < quantity; i++) {
        random_position[i].x = rand() % width;
        random_position[i].y = rand() % height;
    }
    return random_position;
}

static void spawn_resources(map_t *map, resource_e item, float densitiy) {
    uint quantity = resources_quantity(densitiy, map->width, map->height);
    position_t *random_position = random_positions(map, quantity, map->width, map->height);
    uint x = 0;
    uint y = 0;


    for (uint i = 0; i < quantity; i++) {
        x = random_position[i].x;
        y = random_position[i].y;
        // add_resource(map->tiles[y][x].resource, item, 1);
    }
    free(random_position);
}

void spawn_all_resources(map_t * map)
{
    spawn_resources(map, FOOD, FOOD_DENSITY);
    spawn_resources(map, LINEMATE, LINEMATE_DENSITY);
    spawn_resources(map, DERAUMERE, DERAUMERE_DENSITY);
    spawn_resources(map, SIBUR ,SIBUR_DENSITY);
    spawn_resources(map, MENDIANE ,MENDIANE_DENSITY);
    spawn_resources(map, PHIRAS ,PHIRAS_DENSITY);
    spawn_resources(map, THYSTAME ,THYSTAME_DENSITY);
}

uint *get_resource_ptr(resources_t *resources, resource_e item)
{
    if (!resources)
        return NULL;
    switch (item) {
        case FOOD:
            return &resources->food;
        case LINEMATE:
            return &resources->linemate;
        case DERAUMERE:
            return &resources->deraumere;
        case SIBUR:
            return &resources->sibur;
        case MENDIANE:
            return &resources->mendiane;
        case PHIRAS:
            return &resources->phiras;
        case THYSTAME:
            return &resources->thystame;
        default:
            return NULL;
    }
}

resources_t *create_resources(void)
{
    resources_t *resources = calloc(1, sizeof(resources_t));

    if (!resources)
        return NULL;
    resources->food = 0;
    resources->linemate = 0;
    resources->deraumere = 0;
    resources->sibur = 0;
    resources->mendiane = 0;
    resources->phiras = 0;
    resources->thystame = 0;
    return resources;
}

void destroy_resources(resources_t *resources)
{
    if (resources)
        free(resources);
}
