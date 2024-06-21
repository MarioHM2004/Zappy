/*ser
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** player
*/

#include "game/player.h"
#include "game/event.h"
#include "game/game.h"
#include "game/resources.h"
#include "libs/log.h"
#include "server/action.h"
#include "server/client.h"
#include "server/command.h"
#include <sys/queue.h>
#include <time.h>

bool add_response_to_player(client_list_t *client_list, player_t *player
    , char *response)
{
    client_t *client = NULL;

    if (!player || !client_list)
        return false;
    client = get_client_by_fd(client_list, player->fd);
    if (!client)
        return false;
    add_response(client, response);
    return true;
}

bool move_player(map_t *map,player_t *player, position_t new_pos)
{
    if (!change_players_tile(map, player->pos, -1))
        return false;
    if (!change_players_tile(map, new_pos, 1)) {
        change_players_tile(map, player->pos, 1);
        return false;
    }
    player->pos = new_pos;
    return true;
}

static void handle_player_hunger(server_t *server, player_t *player)
{
    action_t *action = NULL;

    if (player->state != ALIVE)
        return;
    if (player->food_status == 0) {
        if (change_resource(player->inventory, FOOD, -1))
            player->food_status = 126;
        else {
            log_info("Player %d DIED", player->number);
            action = create_action(PLAYER_DEAD, player, sizeof(player_t *));
            player->state = DEAD;
        }
    }
    player->food_status--;
}

void player_tick(server_t *server, player_t *player)
{
    event_node_t *event_node = LIST_FIRST(player->events);

    handle_player_hunger(server, player);
    if (event_node == NULL)
        return;
    if (event_node->wait_time > 0) {
        event_node->wait_time--;
        return;
    }
    handle_ai_event(server, player, event_node->event);
    LIST_REMOVE(event_node, entries);
}
