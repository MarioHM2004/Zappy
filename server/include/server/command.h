/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** command
*/

#ifndef COMMAND_H_
    #define COMMAND_H_

    #include "game/player.h"
    #include "game/team.h"
    #include "server.h"

    #define INCANTATION_NUM 7
    #define MAX_COMMAND_NAME_LENGTH 64
    #define ERROR_MESSAGE "ko"

    // GUI
    #define MSZ_REQUEST "msz"
    #define MSZ_RESPONSE "msz %d %d"
    #define BCT_REQUEST "bct %d %d"
    #define BCT_RESPONSE "bct %d %d %d %d %d %d %d %d %d"
    #define MCT_REQUEST "mct"
    // #define MCT_RESPONSE /* BCT RESPONSE * nbr_tiles */
    #define TNA_REQUEST "tna"
    #define TNA_RESPONSE "tna %s" /* * nbr_teams */
    #define PNW_RESPONSE "pnw %d %d %d %d %d %s"
    #define PPO_REQUEST "ppo %d"
    #define PPO_RESPONSE "ppo %d %d %d %d"
    #define PLV_REQUEST "plv %d"
    #define PLV_RESPONSE "plv %d %d"
    #define PIN_REQUEST "pin %d"
    #define PIN_RESPONSE "pin %d %d %d %d %d %d %d %d %d %d"
    #define PEX_RESPONSE "pex %d"
    #define PBC_RESPONSE "pbc %d %s"
    #define PIC_RESPONSE "pic %d %d %d %s" /* %s == player_numbers */
    #define PIE_RESPONSE "pie %d %d %d"
    #define PFK_RESPONSE "pfk %d"
    #define PDR_RESPONSE "pdr %d %d"
    #define PGT_RESPONSE "pgt %d %d"
    #define PDI_RESPONSE "pdi %d"
    #define ENW_RESPONSE "enw %d %d %d %d"
    #define EBO_RESPONSE "ebo %d"
    #define EDI_RESPONSE "edi %d"
    #define SGT_REQUEST "sgt"
    #define SGT_RESPONSE "sgt %d"
    #define SST_REQUEST "sst %d"
    #define SST_REPONSE "sst %d"
    #define SEG_RESPONSE "seg %s"
    #define SMG_RESPONSE "smg %s"
    #define SUC_RESPONSE "suc"
    #define SBP_RESPONSE "sbp"
    #define EHT_RESPONSE "eht %d"
    #define UNKNOWN_COMMAND "suc"
    #define INVALID_PARAMETERS "sbp"

    // BONUS GUI
    #define PLAYER_MOVE_REQUEST "player_move %d %d %d"
    #define PLAYER_DIE_REQUEST "player_die %d"
    #define INCANTATION_START_REQUEST "incantation_start %d"
    #define INCANTATION_END_REQUEST "incantation_end %d"

    // AI
    #define FORWARD_REQUEST "forward"
    #define FORWARD_RESPONSE "ok"
    #define RIGHT_REQUEST "right"
    #define RIGHT_RESPONSE "ok"
    #define LEFT_REQUEST "left"
    #define LEFT_RESPONSE "ok"
    #define LOOK_REQUEST "look"
    // #define LOOK_RESPONSE "[%s, %s]" /* csv of tile info (tile info is space separated) */
    #define INVENTORY_REQUEST "inventory"
    #define INVENTORY_RESPONSE "[linemate %d, deraumere %d, sibur %d, mendiane %d, phiras %d, thystame %d]"
    #define BROADCAST_REQUEST "broadcast %s"
    #define BROADCAST_SENDER "ok"
    #define BROADCAST_RECEIVER "message %d, %s"
    #define CONNECT_NBR_REQUEST "connect_nbr"
    #define CONNECT_NBR_RESPONSE "%d"
    #define FORK_REQUEST "fork"
    #define FORK_RESPONSE "ok"
    #define EJECT_REQUEST "eject"
    #define EJECT_RESPONSE "ok"
    #define EJECTED_RESPONSE "eject: %d"
    #define DEATH_RESPONSE "dead"
    #define TAKE_OBJECT_REQUEST "take %s"
    #define TAKE_OBJECT_RESPONSE "ok"
    #define SET_OBJECT_REQUEST "set %s"
    #define SET_OBJECT_RESPONSE "ok"
    #define START_INCANTATION_REQUEST "incantation"
    #define START_INCANTATION_RESPONSE "elevation underway"
    #define END_INCANTATION_RESPONSE "current level: %d"
    #define AI_CONNECTION "%d %d"

typedef struct expulsion_thread_s {
    socket_t *socket;
    char *msg;
} expulsion_thread_t;

typedef void (*client_command_func_t)(server_t *, client_t *, char *);

typedef struct client_command_s {
    char name[MAX_COMMAND_NAME_LENGTH];
    client_command_func_t func;
} client_command_t;

void packet_message(client_t *client, const char *message);

// GUI
void msz_command(server_t *server, client_t *client, char *cmd);
void bct_command(server_t *server, client_t *client, char *cmd);
void mct_command(server_t *server, client_t *client, char *cmd);
void tna_command(server_t *server, client_t *client, char *cmd);
void ppo_command(server_t *server, client_t *client, char *cmd);
void plv_command(server_t *server, client_t *client, char *cmd);
void pin_command(server_t *server, client_t *client, char *cmd);
void sgt_command(server_t *server, client_t *client, char *cmd);
void sst_command(server_t *server, client_t *client, char *cmd);
void seg_command(server_t *server, client_t *client, team_t *team);
void pnw_command(server_t *server, client_t *client, player_t *player);
void pdi_command(server_t *server, client_t *client, player_t *player);
void edi_command(server_t *server, client_t *client, player_t *player);
void pfk_command(server_t *server, client_t *client, player_t *player);
void eht_command(server_t *server, client_t *client, player_t *player);
void ebo_command(server_t *server, client_t *client, player_t *player);
void pex_command(server_t *server, client_t *client, player_t *player);
void smg_command(server_t *server, client_t *client, char *msg);
void enw_command(server_t *server, client_t *client, player_t *player,
    player_t *egg);
void pbc_command(server_t *server, client_t *client,
    player_t *player, char *msg);
void pic_command(server_t *server, client_t *client, player_list_t *players);
void pie_command(server_t *server, client_t *client,
    player_t *player, bool res);
void pdr_command(server_t *server, client_t *client,
    player_t *player, resource_e resource);
void pgt_command(server_t *server, client_t *client,
    player_t *player, resource_e resource);

// GUI BONUS
void player_move(server_t *server, client_t *client, char *cmd);
void player_die(server_t *server, client_t *client, char *cmd);
void incantation_start_gui(server_t *server, client_t *client, char *cmd);
void incantation_end_gui(server_t *server, client_t *client, char *cmd);

// AI
void forward_command(server_t *server, client_t *client, char *cmd);
void right_command(server_t *server, client_t *client, char *cmd);
void left_command(server_t *server, client_t *client, char *cmd);
void look_command(server_t *server, client_t *client, char *cmd);
void fork_command(server_t *server, client_t *client, char *cmd);
void eject_command(server_t *server, client_t *client, char *cmd);
void inventory_command(server_t *server, client_t *client, char *cmd);
void connect_nbr_command(server_t *server, client_t *client, char *cmd);
void incantation_command(server_t *server, client_t *client, char *cmd);
void take_object_command(server_t *server, client_t *client, char *cmd);
void set_object_command(server_t *server, client_t *client, char *cmd);
void broadcast_command(server_t *server, client_t *client, char *cmd);

// PENDING
void assign_client_type(server_t *server, client_t *client, char *cmd);

char *get_tile_content(server_t *server, int width, int height);
char *get_cmd_from_packets(packet_list_t *packets);
void add_response(client_t *client, char *response);

bool valid_incantation_tile(tile_t tile, incantation_t incantation);
extern incantation_t incantations[INCANTATION_NUM];

#endif /* !COMMAND_H_ */
