/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** environment
*/

//take object, set object

#include "game/event.h"
#include "game/game.h"
#include "game/map.h"
#include "game/player.h"
#include "game/resources.h"
#include "libs/log.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "server/action.h"
#include "server/client.h"
#include "server/command.h"
#include "server/server.h"
#include "server/action.h"

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

static void take_object_action(server_t *server, player_t *player,
    resource_e resource, bool success)
{
    action_t *ai_action = NULL;
    action_t *gui_action = NULL;
    object_t object = {
        .player = player,
        .resource = resource,
    };

    if (success) {
        log_debug("Player %d took %d from the floor",
            player->number, resource);
        ai_action = create_event_completed_action(player, TAKE_OBJECT,
            TAKE_OBJECT_RESPONSE, true);
        gui_action = create_action(PLAYER_TAKE, &object, sizeof(object_t));
    } else {
        log_debug("Player %d couldn't take any item from the floor",
            player->number);
        ai_action = create_event_completed_action(player, TAKE_OBJECT,
            NULL, false);
    }
    if (ai_action)
        add_action(server->actions, ai_action);
    if (gui_action)
        add_action(server->actions, gui_action);
}


static void consume_food(player_t *player, float freq)
{
    if(change_resource(player->inventory, FOOD, -1)) {
        player->food_status += get_execution_time(126.0, freq);
    }
}

void take_object(server_t *server, player_t *player, event_t *event)
{
    tile_t tile = map_at(server->game->map, player->pos);
    resource_e item = -1;
    client_t *client = get_client_by_fd(server->clients, player->fd);

    if (event->type != TAKE_OBJECT || !client) {
        take_object_action(server, player, item, false);
        return;
    }
    item = event->data.object.resource;
    if (item != -1 && move_item(tile.resource, player->inventory, item)) {
          if (item == 0)
            consume_food(player, server->game->freq);
        take_object_action(server, player, item, true);
    }
    else
        take_object_action(server, player, item, false);
}

static void set_object_action(server_t *server, player_t *player,
    resource_e resource, bool success)
{
    action_t *ai_action = NULL;
    action_t *gui_action = NULL;
    object_t object = {
        .player = player,
        .resource = resource,
    };

    if (success) {
        log_debug("Player %d set  %d from the floor",
            player->number, resource);
        ai_action = create_event_completed_action(player, SET_OBJECT,
            TAKE_OBJECT_RESPONSE, true);
        gui_action = create_action(PLAYER_SET, &object, sizeof(object_t));
    } else {
        log_debug("Player %d couldn't set any item from the floor",
            player->number);
        ai_action = create_event_completed_action(player, SET_OBJECT,
            NULL, false);
    }
    if (ai_action)
        add_action(server->actions, ai_action);
    if (gui_action)
        add_action(server->actions, gui_action);
}

void set_object(server_t *server, player_t *player, event_t *event)
{
    tile_t tile = map_at(server->game->map, player->pos);
    resource_e item = -1;
    client_t *client = get_client_by_fd(server->clients, player->fd);

    if (event->type != SET_OBJECT || !client) {
        set_object_action(server, player, item, false);
        return;
    }
    item = event->data.object.resource;
    if (item != -1 && move_item(player->inventory, tile.resource, item))
        set_object_action(server, player, item, true);
    else
        set_object_action(server, player, item, false);
}
