/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** command_utils
*/

#include "libs/lib.h"
#include "server/command.h"
#include "zappy.h"
#include <stdlib.h>
#include <string.h>

static bool is_packet_completed(packet_t *packet)
{
    if (!packet)
        return false;
    for (size_t i = 0; packet->data[i]; i++) {
        if (strstr(packet->data, CRLF))
            return true;
    }
    return false;
}

char *get_cmd_from_packets(packet_list_t *packets)
{
    char *cmd = calloc(MAX_COMMAND_LENGTH, sizeof(char));
    packet_node_t *tmp = NULL;
    packet_node_t *current = NULL;

    if (!packets)
        return NULL;
    strcpy(cmd, packets->lh_first->packet->data);
    current = LIST_FIRST(packets);
    while (current != NULL) {
        tmp = LIST_NEXT(current, entries);
        LIST_REMOVE(current, entries);
        if (!current->packet || is_packet_completed(current->packet))
            break;
        cmd = safe_strcat(cmd, current->packet->data);
        destroy_packet_node(current);
        current = tmp;
    }
    cmd[strlen(cmd) - strlen(CRLF) - 1] = '\0';
    return cmd;
}

