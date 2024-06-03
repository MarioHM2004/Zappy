/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** resources
*/

#ifndef RESOURCES_H_
#define RESOURCES_H_

#include <stdbool.h>
#include <sys/types.h>

    #define FOOD_DENSITY 0.5
    #define LINEMATE_DENSITY 0.3
    #define DERAUMERE_DENSITY 0.15
    #define SIBUR_DENSITY 0.1
    #define MENDIANE_DENSITY 0.1
    #define PHIRAS_DENSITY 0.08
    #define THYSTAME_DENSITY 0.05
    #define TOTAL_RESOURCES 7

typedef enum {
    FOOD = 0,
    LINEMATE = 1,
    DERAUMERE = 2,
    SIBUR = 3,
    MENDIANE = 4,
    PHIRAS = 5,
    THYSTAME = 6,
    NONE = 7
}resource_e;

typedef struct resources_s {
    uint food;
    uint linemate;
    uint deraumere;
    uint sibur;
    uint mendiane;
    uint phiras;
    uint thystame;
} resources_t;

typedef struct message_to_resource_s {
    char *message;
    resource_e resource;
} message_to_resource_t;

typedef struct map_s map_t;

resources_t *create_resources(void);
void destroy_resources(resources_t *rs);

void spawn_all_resources(map_t *map);
uint *get_resource_ptr(resources_t *resources, resource_e item);
bool move_item(resources_t *src, resources_t *dest, resource_e item);
bool change_resource(resources_t *resources, resource_e item, uint quantity);

//message_to_resource_t msg_to_resource[TOTAL_RESOURCES];
#endif /* !RESOURCES_H_ */
