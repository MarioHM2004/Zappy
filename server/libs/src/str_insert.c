/*
** EPITECH PROJECT, 2024
** B-NWP-400-BAR-4-1-myteams-gonzalo.larroya-martinez
** File description:
** str_insert
*/

#include "lib.h"
#include <string.h>

char *str_insert(char *str, const char *insert)
{
    char *tmp = calloc(strlen(str), sizeof(char));

    if (!tmp)
        return NULL;
    strcpy(tmp, insert);
    strcat(tmp, str);
    strcpy(str, tmp);
    free(tmp);
    return str;
}

char *safe_strcat(char const *src, char const *concat)
{
    int length = strlen(concat) + strlen(src);
    char *res = calloc(length + 1, sizeof(char));

    strcpy(res, src);
    strcat(res, concat);
    return (res);
}