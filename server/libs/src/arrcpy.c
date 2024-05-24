/*
** EPITECH PROJECT, 2024
** B-NWP-400-BAR-4-1-myftp-oriol.linan
** File description:
** arrcpy
*/

#include "lib.h"

void **arrcpy(void **arr)
{
    size_t n = arrlen(arr);
    void **new_arr = calloc(n + 1, sizeof(void *));

    for (size_t i = 0; i < n; i++)
        new_arr[i] = strdup(arr[i]);
    new_arr[n] = NULL;
    return new_arr;
}
