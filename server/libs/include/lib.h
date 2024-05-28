/*
** EPITECH PROJECT, 2024
** B-NWP-400-BAR-4-1-myftp-oriol.linan
** File description:
** lib
*/

#ifndef LIB_H_
    #define LIB_H_

    #include <stdbool.h>
    #include <stdlib.h>
    #include <string.h>
    #include <stdarg.h>

char **split(const char *str, char *separator);
size_t arrlen(void **arr);
void freearr(void **arr);
char *formatstr(const char *format, ...);
char *formatstr_va(const char *format, va_list args);
char *join(char **arr, char *sep);
void **arrcpy(void **arr);
void **arrcat(void **arr1, void **arr2);
bool startswith(const char *str, const char *start);
bool endswith(const char *str, const char *end);
char *str_insert(char *str, const char *insert);
void *load_library(const char *path);
char *safe_strcat(char const *src, char const *concat);
#endif /* !LIB_H_ */
