/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** game_create
*/

#include "game/event.h"
#include "game/game.h"
#include "game/map.h"
#include "server/client.h"
#include "server/command.h"
#include "server/server.h"
#include "game/player.h"
#include "game/team.h"
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>


static player_t *get_egg_from_team(team_t *team)
{
    player_node_t *tmp = NULL;

    LIST_FOREACH(tmp, team->players, entries) {
        if (tmp->player && tmp->player->state == EGG)
            return tmp->player;
    }
    return NULL;
}

player_t *assign_player(socket_t *socket, server_t *server, char *team_name)
{
    static int player_count = 0;
    client_t *client = get_client_by_fd(server->clients, socket->fd);
    team_t *team = get_team_by_name(server->game, team_name);
    player_t *egg = NULL;
    if (!team || !client)
        return NULL;
    egg = get_egg_from_team(team);
    if (!egg)
        return NULL;
    change_eggs_tile(server->game->map, egg->pos, -1);
    change_players_tile(server->game->map, egg->pos, 1);
    egg->state = ALIVE;
    egg->fd = socket->fd;
    egg->food_status = get_execution_time(1260, server->game->freq);
    ebo_command(server, client, egg);
    return egg;
}

player_t *create_egg(map_t *map, position_t pos)
{
    player_t *player = calloc(1, sizeof(player_t));

    if (!player)
        return NULL;
    player->fd = -1;
    player->number = 0;
    player->pos = pos;
    change_eggs_tile(map, player->pos, +1);
    player->dir = get_random_dir();
    player->level = 1;
    player->state = EGG;
    player->inventory = create_resources();
    player->events = create_event_list();
    if (player->inventory == NULL) {
        free(player);
        return NULL;
    }
    return player;
}

player_t *spawn_egg(map_t *map)
{
    player_t *player = calloc(1, sizeof(player_t));
    static int player_count = 1;

    if (!player)
        return NULL;

    player->fd = -1;
    player->number = player_count;
    player_count++;
    player->pos = get_random_pos(map);
    change_eggs_tile(map, player->pos, +1);
    player->dir = get_random_dir();
    player->level = 1;
    player->state = EGG;
    player->inventory = create_resources();
    player->events = create_event_list();
    if (player->inventory == NULL) {
        free(player);
        return NULL;
    }
    return player;
}

player_node_t *create_player_node(player_t *p)
{
    player_node_t *pn = calloc(1, sizeof(player_node_t));

    if (!pn)
        return NULL;
    pn->player = p;
    return pn;
}

player_list_t *create_player_list(void)
{
    player_list_t *head = calloc(1, sizeof(player_list_t));

    if (!head)
        return NULL;
    LIST_INIT(head);
    return head;
}
