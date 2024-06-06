/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** command
*/

#ifndef COMMAND_H_
    #define COMMAND_H_

    #include "server.h"

    #define MAX_COMMAND_NAME_LENGTH 64
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
    #define PIC_RESPONSE "pic %d %d %s" /* %s == player_numbers */
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

    #define ERROR_MESSAGE "ko"
    #define UNKNOWN_COMMAND "suc"
    #define INVALID_PARAMETERS "sbp"

typedef void (*client_command_func_t)(server_t *, client_t *, char *);

typedef struct client_command_s {
    char name[MAX_COMMAND_NAME_LENGTH];
    client_command_func_t func;
} client_command_t;

void packet_message(client_t *client, const char *message);
void msz_command(server_t *server, client_t *client, char *cmd);
void bct_command(server_t *server, client_t *client, char *cmd);
void mct_command(server_t *server, client_t *client, char *cmd);
void tna_command(server_t *server, client_t *client, char *cmd);
void ppo_command(server_t *server, client_t *client, char *cmd);
void plv_command(server_t *server, client_t *client, char *cmd);
void pin_command(server_t *server, client_t *client, char *cmd);
void sgt_command(server_t *server, client_t *client, char *cmd);
void sst_command(server_t *server, client_t *client, char *cmd);
void seg_command(server_t *server, client_t *client);

char *get_tile_content(server_t *server, int width, int height);
char *get_cmd_from_packets(packet_list_t *packets);

#endif /* !COMMAND_H_ */
