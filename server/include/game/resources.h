/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** resources
*/

#ifndef RESOURCES_H_
#define RESOURCES_H_

#include <sys/types.h>

    #define FOOD_DENSITY 0.5
    #define LINEMATE_DENSITY 0.3
    #define DERAUMERE_DENSITY 0.15
    #define SIBUR_DENSITY 0.1
    #define MENDIANE_DENSITY 0.1
    #define PHIRAS_DENSITY 0.08
    #define THYSTAME_DENSITY 0.05


enum resource_e {
    FOOD = 1,
    LINEMATE = 2,
    DERAUMERE = 3,
    SIBUR = 4,
    MENDIANE = 5,
    PHIRAS = 6,
    THYSTAME = 7
};

typedef struct resources_s {
    uint food;
    uint linemate;
    uint deraumere;
    uint sibur;
    uint mendiane;
    uint phiras;
    uint thystame;
} resources_t;

typedef struct map_s map_t;

void spawn_all_resources(map_t *map);

#endif /* !RESOURCES_H_ */
