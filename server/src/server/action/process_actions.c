/*
** EPITECH PROJECT, 2024
** action
** File description:
** process_actions
*/

#include "server/action.h"
#include "server/server.h"
#include <sys/queue.h>

void tmp(server_t *, action_t *);

static const action_response_t action_responses[] = {
    { EVENT_COMPLETED, &event_completed },
    { NEW_GUI, &new_gui },
    { NEW_PLAYER, &new_player },
    { PLAYER_MOVED, &player_moved },
    { PLAYER_EJECT, &player_eject },
    { PLAYER_INVENTORY, &player_inventory },
    { PLAYER_SET, &player_set },
    { PLAYER_TAKE, &player_take },
    { PLAYER_BROADCAST, &player_broadcast },
    { PLAYER_FORK, &player_fork },
    { PLAYER_DEAD, &player_dead },
    { INCANTATION_START, &incantation_start },
    { INCANTATION_END, &incantation_end },
    { INCANTATION_COMPLETE, &incantation_complete },
    { EGG_LAYED, &egg_layed },
    { EGG_MATURED, &egg_matured },
    { MAP_REFILL, &map_refill },
};

void process_actions(server_t *server)
{
    action_node_t *node = NULL;
    size_t len = sizeof(action_responses) / sizeof(action_responses[0]);

    LIST_FOREACH(node, server->actions, entries) {
        for (size_t i = 0; i < len; i++) {
            if (action_responses[i].type != node->action->type)
                continue;
            action_responses[i].func(server, action);
            // remove action from list
        }
    }
}

