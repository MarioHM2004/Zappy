/*
** EPITECH PROJECT, 2024
** utils
** File description:
** broadcast
*/

#include "game/event.h"
#include <stdlib.h>
#include <string.h>

broadcast_t *create_broadcast(player_t *player, const char *text)
{
    broadcast_t *broadcast = calloc(1, sizeof(broadcast_t));

    if (!player || !text || !broadcast)
        return NULL;
    broadcast->player = *player;
    strcpy(broadcast->text, text);
    return NULL;
}

void delete_broadcast(broadcast_t *broadcast)
{
    if (!broadcast)
        return;
    free(broadcast);
}

