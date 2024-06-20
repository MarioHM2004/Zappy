/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** information
*/

//*death of a player*, inventory, connect_nbr

#include "game/player.h"
#include "game/team.h"
#include "libs/lib.h"
#include "libs/log.h"
#include "server/action.h"
#include "server/client.h"
#include "server/command.h"
#include "server/server.h"
#include <stdbool.h>

void inventory(server_t *server, player_t *player, event_t *event)
{
    action_t *action = NULL;

    char *inventory = formatstr("[food %d, linemate %d, deraumere %d, sibur %d, "
        "mendiane %d, phiras %d, thystame %d]",
        player->inventory->food,
        player->inventory->linemate,
        player->inventory->deraumere,
        player->inventory->sibur,
        player->inventory->mendiane,
        player->inventory->phiras,
        player->inventory->thystame);
    log_debug("Player %d inventory: %s", player->number, inventory);
    action = create_event_completed_action(player, INVENTORY, inventory, true);
    if (action)
        add_action(server->actions, action);
}

