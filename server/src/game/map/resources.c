/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** resources
*/

#include "game/map.h"
#include <stdlib.h>

static uint resources_quantity(float density, uint width, uint height)
{
    int quantity = ((width * height) * density);

    if (quantity < 1)
        return 1;
    return (uint)quantity;
}

static position_t **random_positions(uint quantity, uint width, uint height)
{
    position_t **random_position = calloc(quantity + 1, sizeof(position_t *));

    if (!random_position)
        return NULL;

    for (uint i = 0; i < quantity; i++) {
        random_position[i] = calloc(1, sizeof(position_t));
        if (!random_position[i])
            return NULL;
        random_position[i]->x = rand() % width;
        random_position[i]->y = rand() % height;
    }
    random_position[quantity] = NULL;
    return random_position;
}

static void spawn_resources(map_t *map, float densitiy) {
    uint quantity = resources_quantity(densitiy, map->width, map->height);
    position_t **random_position = random_positions(quantity, map->width, map->height);
    uint x = 0;
    uint y = 0;

    for (uint i = 0; random_position[i]; i++) {
        x = random_position[i]->x;
        y = random_position[i]->y;
        map->tiles[x][y]->resources->food++;
        free(random_position[i]);
    }
    free(random_position);
}

void spawn_all_resources(map_t * map)
{
    spawn_resources(map, FOOD_DENSITY);
    spawn_resources(map, LINEMATE_DENSITY);
    spawn_resources(map, DERAUMERE_DENSITY);
    spawn_resources(map, SIBUR_DENSITY);
    spawn_resources(map, MENDIANE_DENSITY);
    spawn_resources(map, PHIRAS_DENSITY);
    spawn_resources(map, THYSTAME_DENSITY);
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
