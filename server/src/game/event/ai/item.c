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
#include "server/client.h"
#include "server/command.h"
#include "server/server.h"

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
    return -1;
}

void take_object(server_t *server, player_t *player, event_t *event)
{
    tile_t tile = map_at(server->game->map, player->pos);
    resource_e item;
    uint *resource;
    client_t *client = get_client_by_fd(server->clients, player->fd);

    if (event->type != TAKE_OBJECT || !client) {
        add_response_to_player(server->clients, player, ERROR_MESSAGE);
        return;
    }
    item = string_to_resource(event->data.object.name);
    if (item != -1 && move_item(tile.resource, player->inventory, item)) {
        log_debug("Player %d took %d from the floor", player->number, item);
        pgt_command(server, client, player, item);
        add_response_to_player(server->clients, player,
            TAKE_OBJECT_RESPONSE);
    } else {
        log_debug("Player %d couldn't take any item from the floor",
            player->number);
        add_response_to_player(server->clients, player, ERROR_MESSAGE);
    }
}

void set_object(server_t *server, player_t *player, event_t *event)
{
    tile_t tile = map_at(server->game->map, player->pos);
    resource_e item;
    uint *resource;
    client_t *client = get_client_by_fd(server->clients, player->fd);

    if (event->type != SET_OBJECT || !client) {
        add_response_to_player(server->clients, player, ERROR_MESSAGE);
        return;
    }
    item = string_to_resource(event->data.object.name);
    if (item != -1 && move_item(player->inventory, tile.resource, item)) {
        log_debug("Player %d set %d on the floor", player->number, item);
        pdr_command(server, client, player, item);
        add_response_to_player(server->clients, player,
            SET_OBJECT_RESPONSE);
    } else {
        log_debug("Player %d couldn't set %s on the floor",
        player->number, item);
        add_response_to_player(server->clients, player, ERROR_MESSAGE);
    }

}
