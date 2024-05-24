/*
** EPITECH PROJECT, 2024
** B-NWP-400-BAR-4-1-myftp-oriol.linan
** File description:
** arrlen
*/

#include <stddef.h>
#include "lib.h"

size_t arrlen(void **arr)
{
    size_t n = 0;

    if (!arr)
        return (0);
    while (arr[n] != NULL)
        n++;
    return n;
}
