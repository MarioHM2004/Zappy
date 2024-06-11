/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** environment
*/

//take object, set object

#include "game/event.h"
#include "game/map.h"
#include "game/player.h"
#include "game/resources.h"
#include "libs/log.h"
#include <string.h>


message_to_resource_t msg_to_resource[TOTAL_RESOURCES] = {
    { "food", FOOD },
    { "linemate", LINEMATE },
    { "deraumere", DERAUMERE },
    { "sibur", SIBUR },
    { "mendiane", MENDIANE },
    { "phiras", PHIRAS },
    { "thystame", THYSTAME },
};

static resource_e string_to_resource(char message[MAX_OBJECT_LENGTH])
{
    for (int i = 0; i < TOTAL_RESOURCES; i++) {
        if (strcmp(msg_to_resource[i].message, message) == 0) {
            return msg_to_resource[i].resource;
        }
    }
    return 0;
}

void take_object(game_t *game, player_t *player, event_t *event)
{
    tile_t tile = map_at(game->map, player->pos);
    resource_e item;
    uint *resource;

    if (event->type != TAKE_OBJECT)
        return;
    item = string_to_resource(event->data.object.message);
    if (move_item(tile.resource, player->inventory, item)) {
        log_debug("Player with fd %d took %s from the floor",
        player->fd, item);
    } else {
        log_debug("Player with fd %d couldn't take %s from the floor",
        player->fd, item);
    }
}

void set_object(game_t *game, player_t *player, event_t *event)
{
    tile_t tile = map_at(game->map, player->pos);
    resource_e item;
    uint *resource;

    if (event->type != SET_OBJECT)
        return;
    item = string_to_resource(event->data.object.message);
    if (move_item(player->inventory, tile.resource, item)) {
        log_debug("Player with fd %d set %s on the floor",
        player->fd, item);
    } else {
        log_debug("Player with fd %d couldn't set %s on the floor",
        player->fd, item);
    }

}