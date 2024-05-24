/*
** EPITECH PROJECT, 2024
** B-NWP-400-BAR-4-1-myftp-oriol.linan
** File description:
** formatstr
*/

#include <stdio.h>
#include "lib.h"

static char *get_formatstr(const char *format, va_list args, va_list cpy)
{
    int bufferSize = vsnprintf(NULL, 0, format, args) + 1;
    char *buffer = calloc(bufferSize, sizeof(char));

    if (!buffer)
        return NULL;
    vsnprintf(buffer, bufferSize, format, cpy);
    return buffer;
}

char *formatstr(const char *format, ...)
{
    va_list args;
    va_list cpy;
    char *buffer = NULL;

    va_start(args, format);
    va_copy(cpy, args);
    buffer = get_formatstr(format, args, cpy);
    va_end(args);
    va_end(cpy);
    return buffer;
}

char *formatstr_va(const char *format, va_list args)
{
    va_list cpy;
    char *buffer = NULL;

    va_copy(cpy, args);
    buffer = get_formatstr(format, args, cpy);
    va_end(cpy);
    return buffer;
}
