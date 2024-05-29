/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** process_packets
*/

#include "server/server.h"
#include <stdlib.h>
#include <string.h>
#include "libs/lib.h"

static bool is_packed_completed(packet_t *packet)
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
    char *cmd = calloc(2056, sizeof(char));
    packet_node_t *tmp = NULL;
    packet_node_t *current = NULL;

    if (!packets)
        return NULL;
    strcpy(cmd, packets->lh_first->packet->data);
    current = LIST_FIRST(packets);
    while (current != NULL) {
        tmp = LIST_NEXT(current, entries);
        LIST_REMOVE(current, entries);
        if (!current->packet || is_packed_completed(current->packet))
            break;
        cmd = safe_strcat(cmd, current->packet->data);
        destroy_packet_node(current);
        current = tmp;

    }
    return cmd;
}

// client_commands_ptr(server, client, cmd);
void process_client_packets(server_t *server, client_t *client)
{
    char *cmd = NULL;
    packet_t *packet = NULL;

    while (!LIST_EMPTY(client->request)) {
        cmd = get_cmd_from_packets(client->request);
    }
}
