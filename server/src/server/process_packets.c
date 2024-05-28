/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** process_packets
*/

#include "server/server.h"

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
    char *cmd = calloc(MAX_BODY_LENGTH, sizeof(char));
    packet_node_t *tmp = NULL;

    if (!packets)
        return NULL;
    strcpy(cmd, packets->lh_first->packet->data);
    LIST_FOREACH(tmp, packets, entries) {
        if (!tmp->packet || is_packed_completed(tmp->packet))
            break;
        cmd = safe_strcat(cmd, tmp->packet->data);
    }
    return cmd;
}

// client_commands_ptr(client, cmd);
void process_client_packets(client_t *client)
{
    char *cmd = get_cmd_from_packets(client->request);
    packet_t *packet = NULL;
}

// gui_commands_ptr(gui, cmd);
void process_gui_packets(gui_t *gui)
{
    char *cmd = get_cmd_from_packets(gui->request);
    packet_t *packet = NULL;
}

// pendings_commands_ptr(gui, cmd);
void process_pendings_packets(pending_t *pendings)
{
    char *cmd = get_cmd_from_packets(pendings->request);
    packet_t *packet = NULL;
}