/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** socket_utils
*/

#include "server/packet.h"
#include "server/socket.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "libs/log.h"
#include <arpa/inet.h>

bool write_socket(socket_t *socket, packet_t *packet)
{
    if (!socket || !packet)
        return false;
    if (write(socket->fd, packet->data, strlen(packet->data)) < 0)
        return false;
    return true;
}

packet_t *read_socket(socket_t *socket)
{
    ssize_t n = 0;
    packet_t *packet = create_packet("");

    if (!socket || !packet)
        return NULL;
    n = read(socket->fd, packet->data, MAX_PACKET_SIZE);
    if (n <= 0)
        return NULL;
    packet->data[n] = '\0';
    return packet;
}

void log_socket(socket_t *socket)
{
    char *mode = NULL;

    if (!socket)
        return;
    if (socket->mode == READ)
        mode = "READ";
    else if (socket->mode == WRITE)
        mode = "WRITE";
    else if (socket->mode == EXCEPT)
        mode = "EXCEPT";
    log_info("Socket={fd=%d, ip=%s, port=%d, mode=%s}", socket->fd,
        inet_ntoa(socket->addr.sin_addr), ntohs(socket->addr.sin_port), mode);
}