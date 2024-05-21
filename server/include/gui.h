/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** gui
*/

#ifndef GUI_H_
#define GUI_H_

#include "packet.h"
#include "socket.h"

typedef struct gui_s {
    socket_t *socket;
    packet_list_t *packets;
} gui_t;

#endif /* !GUI_H_ */
