/*
** EPITECH PROJECT, 2024
** B-NWP-400-BAR-4-1-myftp-oriol.linan
** File description:
** split
*/

#include "libs/lib.h"
#include <string.h>

static char **split_str(char *str, char *separator)
{
    char **arr = NULL;
    char **tmp = NULL;
    char *token = NULL;

    if (!str)
        return NULL;
    token = strtok(str, separator);
    for (int i = 0; token; i++) {
        tmp = reallocarray(arr, i + 2, sizeof(char *));
        if (!tmp) {
            free(arr);
            return NULL;
        }
        arr = tmp;
        arr[i + 1] = NULL;
        arr[i] = strdup(token);
        token = strtok(NULL, separator);
    }
    return arr;
}

char **split(const char *str, char *separator)
{
    char **ret = NULL;
    char *cpy = NULL;

    if (!str)
        return NULL;
    cpy = strdup(str);
    ret = split_str(cpy, separator);
    free(cpy);
    return ret;
}
