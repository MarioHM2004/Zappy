/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** client_list
*/

#include "server/client.h"
#include "server/packet.h"

client_node_t *create_client_node(client_t *c)
{
    client_node_t *node = calloc(1, sizeof(client_node_t));

    if (!node)
        return NULL;
    node->client = c;
    return node;
}

client_list_t *create_client_list(void)
{
    client_list_t *head = calloc(1, sizeof(client_list_t));

    if (!head)
        return NULL;
    LIST_INIT(head);
    return head;
}

void destroy_client_node(client_node_t *cn)
{
    if (!cn)
        return;
    destroy_client(cn->client);
    free(cn);
}

void destroy_client_list(client_list_t *head)
{
    client_node_t *tmp = NULL;
    client_node_t *current = NULL;

    if (!head)
        return;
    current = LIST_FIRST(head);
    while (current != NULL) {
        tmp = LIST_NEXT(current, entries);
        LIST_REMOVE(current, entries);
        destroy_packet_node(current);
        free(current);
        current = tmp;
    }
}
