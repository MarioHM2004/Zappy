/*
** EPITECH PROJECT, 2024
** B-NWP-400-BAR-4-1-myftp-oriol.linan
** File description:
** endswith
*/

#include "libs/lib.h"
#include <string.h>

bool endswith(const char *str, const char *end)
{
    int len = strlen(str);
    int end_len = strlen(end);

    if (len < end_len)
        return false;
    return strncmp(str + len - end_len, end, end_len) == 0 ? true : false;
}
