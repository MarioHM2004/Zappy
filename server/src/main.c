/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** main
*/

#include "parser.h"
#include "server/server.h"
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv)
{
    arguments_t *arguments = parser(argc, argv);
    server_t *server = NULL;

    srand(time(NULL));
    if (!arguments)
        return 84;
    server = create_server(arguments);
    if (!server)
        return 84;
    run(server);
    return 0;
}
