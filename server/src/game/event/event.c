/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** event
*/

#include "game/event.h"
#include "libs/log.h"
#include <time.h>

event_func_ptr_t event_func_ptr[] = {
    {FORWARD, &forward},
    {TURN_RIGHT, &turn_right},
    {TURN_LEFT, &turn_left},
    {LOOK, &look},
    {INVENTORY, &inventory},
    {BROADCAST, &broadcast},
    {CONNECT_NBR, &connect_nbr},
    {FORK, &fork_player},
    {EJECT, &eject},
    {TAKE_OBJECT, &take_object},
    {SET_OBJECT, &set_object},
    {START_INCANTATION, &incantation},
    {0, NULL}
};

void handle_ai_event(game_t *game, player_t *player, event_t *event)
{
    for (int i = 0; event_func_ptr[i].func != NULL; i++) {
        if (event_func_ptr[i].type == event->type) {
                //log_debug("Handling event %d", event->type);
            event_func_ptr[i].func(game, player, event);
            return;
        }
    }
}
