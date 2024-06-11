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
    log_debug("Player with fd %d requested inventory", player->fd);
    log_debug("[");
    log_debug("food %d, ", player->inventory->food);
    log_debug("linemate %d, ", player->inventory->linemate);
    log_debug("deraumere %d, ", player->inventory->deraumere);
    log_debug("sibur %d, ", player->inventory->sibur);
    log_debug("mendiane %d, ", player->inventory->mendiane);
    log_debug("phiras %d, ", player->inventory->phiras);
    log_debug("thystame %d", player->inventory->thystame);
    log_debug("]\n");
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
    log_debug("Player with fd %d requested connect_nbr", player->fd);
    log_debug("Team %s has %d unused slots", team->name, size);
    printf("%d\n", size);
}