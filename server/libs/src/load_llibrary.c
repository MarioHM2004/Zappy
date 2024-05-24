/*
** EPITECH PROJECT, 2024
** B-NWP-400-BAR-4-1-myteams-gonzalo.larroya-martinez
** File description:
** load_llibrary
*/

#include <dlfcn.h>
#include <stddef.h>

void *load_library(const char *path)
{
    void *handle = dlopen(path, RTLD_LAZY);

    if (!handle)
        return NULL;
    return handle;
}
