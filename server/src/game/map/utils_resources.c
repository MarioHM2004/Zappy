/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** utils_resources
*/

#include "game/map.h"

bool move_item(resources_t *src, resources_t *dest, resource_e item)
{
    if (change_resource(src, item, -1) == false)
        return false;
    if (change_resource(dest, item, 1) == false)
        return false;
    return true;
}

bool change_resource(resources_t *resources, resource_e item, uint quantity)
{
    uint *resource = get_resource_ptr(resources, item);

    if (resource == NULL)
        return false;
    if (*resource + quantity < 0)
        return false;
    *resource += quantity;
    return true;
}

