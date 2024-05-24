/*
** EPITECH PROJECT, 2024
** B-NWP-400-BAR-4-1-myftp-oriol.linan
** File description:
** arrcat
*/

#include "lib.h"

void **arrcat(void **arr1, void **arr2)
{
    size_t len1 = arrlen(arr1);
    size_t len2 = arrlen(arr2);
    void **new_arr = calloc(len1 + len2 + 1, sizeof(void *));

    if (!new_arr)
        return NULL;
    for (size_t i = 0; i < len1; i++)
        new_arr[i] = strdup(arr1[i]);
    for (size_t i = 0; i < len2; i++)
        new_arr[len1 + i] = strdup(arr2[i]);
    new_arr[len1 + len2] = NULL;
    return new_arr;
}
