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
    #include <sys/queue.h>

typedef struct gui_s {
    socket_t *socket;
    packet_list_t *request;
    packet_list_t *response;
} gui_t;

typedef struct gui_node_s {
    gui_t *gui;
    LIST_ENTRY(gui_node_s) entries;
} gui_node_t;

typedef struct gui_list_s {
    struct gui_node_s *lh_first;
} gui_list_t;

gui_t *create_gui(socket_t *socket);
gui_node_t *create_gui_node(gui_t *gui);
gui_list_t *create_gui_list(void);
void destroy_gui(gui_t *g);
void destroy_gui_node(gui_node_t *node);
void destroy_gui_list(gui_list_t *list);

#endif /* !GUI_H_ */
