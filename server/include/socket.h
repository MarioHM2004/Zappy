/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** socket
*/

#ifndef SOCKET_H_
    #define SOCKET_H_

#include <netinet/in.h>
#include <stdbool.h>
#include <sys/queue.h>

typedef enum {
    READ,
    WRITE,
    EXCEPT
} fd_mode_t;

typedef struct socket_s {
    int fd;
    struct sockaddr_in addr;
    socklen_t addr_len;
    fd_mode_t mode;
    bool connected;
} socket_t;

socket_t *create_socket(int port, in_addr_t addr);
void destroy_socket(socket_t *s);

bool bind_socket(socket_t *s);
bool listen_socket(socket_t *s, int backlog);
socket_t *accept_socket(socket_t *s);

#endif /* !SOCKET_H_ */
