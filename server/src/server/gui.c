/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** gui
*/

#include "server/gui.h"
#include "server/packet.h"

gui_t *create_gui(socket_t *socket)
{
    gui_t *new_gui = calloc(1, sizeof(gui_t));

    if (!new_gui)
        return NULL;
    new_gui->socket = socket;
    new_gui->request = create_packet_list();
    new_gui->request = create_packet_list();
    if (!new_gui->request || !new_gui->response) {
        destroy_gui(new_gui);
        return NULL;
    }
    return new_gui;
}

void destroy_gui(gui_t *g)
{
    if (!g)
        return;
    destroy_socket(g->socket);
    destroy_packet_list(g->request);
    destroy_packet_list(g->response);
    free(g);
}
