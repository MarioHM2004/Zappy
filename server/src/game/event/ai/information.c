/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** information
*/

//*death of a player*, inventory, connect_nbr

#include "game/player.h"
#include "game/team.h"
#include "libs/log.h"

static void log_inventory(player_t *player)
{
    log_debug("PLayer %d requested inventory [food %d, linemate %d, "
              "deraumere %d, sibur %d, mendiane %d, phiras %d, thystame %d]\n",
              player->number,
              player->inventory->food,
              player->inventory->linemate,
              player->inventory->deraumere,
              player->inventory->sibur,
              player->inventory->mendiane,
              player->inventory->phiras,
              player->inventory->thystame);
}


void inventory(game_t *game, player_t *player, event_t *event)
{
    log_inventory(player);
}

void connect_nbr(game_t *game, player_t *player, event_t *event)
{
    team_t *team = get_team_by_player(game, player);
    uint size = 0;

    if (!team)
        return;

    size = get_player_list_size(team->players);
    log_debug("Player %d requested connect_nbr", player->number);
    log_debug("Team %s has %d unused slots", team->name, size);
    printf("%d\n", size);
}