/*
** EPITECH PROJECT, 2024
** B-YEP-400-BAR-4-1-zappy-joan-pau.merida-ruiz
** File description:
** game_utils
*/

#include "libs/log.h"

float get_execution_time(float execution_time, float frequence)
{
    if (frequence == 0) {
        log_fatal("Frequence should not be 0");
        return execution_time;
    }
    return execution_time / frequence;

}
