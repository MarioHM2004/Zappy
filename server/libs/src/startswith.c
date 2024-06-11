/*
** EPITECH PROJECT, 2024
** B-NWP-400-BAR-4-1-myftp-oriol.linan
** File description:
** startswith
*/

#include "libs/lib.h"
#include <string.h>

bool startswith(const char *str, const char *start)
{
    return strncmp(str, start, strlen(start)) == 0 ? true : false;
}
