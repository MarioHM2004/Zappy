/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** packet
*/

#ifndef PACKET_H_
    #define PACKET_H_

    #include <sys/queue.h>

    #define MAX_PACKET_SIZE 1024 * 5

typedef struct packet_s {
    char data[MAX_PACKET_SIZE];
} packet_t;

typedef struct packet_node_s {
    packet_t *packet;
    LIST_ENTRY(packet_node_s) entries;
} packet_node_t;

typedef struct packet_list_s {
    struct packet_node_s *lh_first;
} packet_list_t;

packet_t *create_packet(const char *data);
packet_node_t *create_packet_node(packet_t *p);
packet_list_t *create_packet_list(void);
void destroy_packet(packet_t *p);
void destroy_packet_node(packet_node_t *pn);
void destroy_packet_list(packet_list_t *head);

void add_packet(packet_list_t *packets, packet_t *packet);

#endif /* !PACKET_H_ */
