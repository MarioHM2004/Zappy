/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** send_packets
*/

#include "server/server.h"

// make one for each type (gui, client, pendings)
// void process_packets(packet_list_t *packets)
// {
//     char *cmd = get_cmd_from_packets(packets);

//     if (client->packet_to_send != NULL) {
//         write_socket(client->socket, client->packet_to_send);
//         destroy_packet(client->packet_to_send);
//         client->packet_to_send = NULL;
//     } else {
//         packet = commands_ptr(server, client, full_cmd);
//         if (packet) {
//             write_socket(client->socket, packet);
//             destroy_packet(packet);
//         }
//     }
// }

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

// add safe strcat
char *get_cmd_from_packets(packet_list_t *packets)
{
    char *cmd = calloc(MAX_BODY_LENGTH, sizeof(char));
    packet_node_t *tmp = NULL;

    if (!packets)
        return NULL;
    strcpy(cmd, packets->lh_first->packet->data);
    LIST_FOREACH(tmp, packets, entries) {
        if (!current->packet && is_packed_completed(current->packet))
            break;
    }
    return cmd;
}

void write_packets(socket_t *socket, packet_list_t **packets)
{
    packet_node_t *tmp = NULL;

    if (!packets)
        return;
    LIST_FOREACH(tmp, *packets, entries) {
        if (!tmp->packet)
            continue;
        write_socket(socket, tmp->packet);
    }
    destroy_packet_list(*packets);
    *packets = create_packet_list();
    client->socket->mode = READ;
}
