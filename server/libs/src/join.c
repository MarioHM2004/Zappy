/*
** EPITECH PROJECT, 2024
** B-NWP-400-BAR-4-1-myftp-oriol.linan
** File description:
** join
*/

#include "lib.h"

static size_t total_len(char **arr, char *sep)
{
    size_t n = 0;

    for (int i = 0; arr && arr[i]; i++) {
        n += strlen(arr[i]);
        if (arr[i + 1])
            n += strlen(sep);
    }
    return n;
}

char *join(char **arr, char *sep)
{
    char *str = calloc(total_len(arr, sep) + 1, sizeof(char));

    if (!str)
        return NULL;
    for (int i = 0; arr && arr[i]; i++) {
        strcat(str, arr[i]);
        if (arr[i + 1])
            strcat(str, sep);
    }
    return str;
}
