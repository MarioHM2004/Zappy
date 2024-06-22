/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** pdi
*/

#include "libs/lib.h"
#include "server/command.h"
#include "game/player.h"
#include "server/socket.h"
#include <pthread.h>
#include <string.h>
#include <unistd.h>

static void *send_expulsion(void *arg)
{
    socket_t *socket = ((expulsion_thread_t *)arg)->socket;
    char *msg = ((expulsion_thread_t *)arg)->msg;

    sleep(2);
    write(socket->fd, msg, strlen(msg));
    write(socket->fd, CRLF, strlen(CRLF));
    free(arg);
    return NULL;
}

void pdi_command(server_t *server, client_t *client, player_t *player)
{
    expulsion_thread_t *arg = calloc(1, sizeof(expulsion_thread_t));
    pthread_t thread;
    char *response = formatstr(PDI_RESPONSE, (int)player->number);

    if (!player || !response || !arg)
        return packet_message(client, ERROR_MESSAGE);
    add_response(client, response);
    arg->socket = client->socket;
    arg->msg = formatstr(PEX_RESPONSE, player->number);
    pthread_create(&thread, NULL, send_expulsion, (void *)arg);
    free(response);
}
