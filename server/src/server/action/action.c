/*
** EPITECH PROJECT, 2024
** action
** File description:
** action
*/

#include "server/action.h"
#include <stdlib.h>

static void event_completed_assignation(action_t *a, void *data)
{
    a->data.event_completed = *((event_completed_t *)data);
}

static void event_received_assignation(action_t *a, void *data)
{
    a->data.event_received= *((event_received_t *)data);
}

static void new_connection(action_t *a, void *data)
{
    a->data.client = (client_t *)data;
}

static void player_action(action_t *a, void *data)
{
    a->data.player = (player_t *)data;
}

static void object_action(action_t *a, void *data)
{
    a->data.object = *((object_t *)data);
}

static void broadcast_action(action_t *a, void *data)
{
    a->data.broadcast = *((broadcast_t *)data);
}

static void incantation_action(action_t *a, void *data)
{
    a->data.incantation = *((incantation_action_t *)data);
}

static void egg_action(action_t *a, void *data)
{
    a->data.egg_shell = *((egg_shell_t *) data);
}

static void map_action(action_t *a, void *data)
{
    a->data.map = (map_t *)data;
}

static const action_assign_t action_assignation[] = {
    { EVENT_COMPLETED, &event_completed_assignation },
    { EVENT_RECEIVED, &event_received_assignation },
    { NEW_GUI, &new_connection },
    { NEW_PLAYER, &new_connection },
    { PLAYER_EJECT, &player_action },
    { PLAYER_INVENTORY, &player_action },
    { PLAYER_SET, &object_action },
    { PLAYER_TAKE, &object_action },
    { PLAYER_BROADCAST, &broadcast_action },
    { PLAYER_FORK, &player_action },
    { PLAYER_DEAD, &player_action },
    { INCANTATION_START, &incantation_action },
    { INCANTATION_END, &incantation_action },
    { INCANTATION_COMPLETE, &incantation_action },
    { EGG_LAYED, &egg_action },
    { EGG_MATURED, &egg_action },
    { EGG_DEATH, &player_action},
    { MAP_REFILL, &map_action },
};

action_t *create_action(action_type_e type, void *data, size_t size)
{
    action_t *action = calloc(1, sizeof(action_t));
    size_t len = sizeof(action_assignation) / sizeof(action_assignation[0]);

    if (!action)
        return NULL;
    action->type = type;
    action->size = size;
    for (size_t i = 0; i < len; i++) {
        if (action_assignation[i].type != type)
            continue;
        action_assignation[i].func(action, data);
        return action;
    }
    destroy_action(action);
    return NULL;
}

void destroy_action(action_t *a)
{
    if (!a)
        return;
    free(a);
}

