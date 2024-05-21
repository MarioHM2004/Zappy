/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** socket
*/

#ifndef SOCKET_H_
#define SOCKET_H_

#include <netinet/in.h>

typedef struct socket_s {
    int fd;
    struct sockaddr_in addr;
    socklen_t addr_len;
} socket_t;

#endif /* !SOCKET_H_ */
