// error.c
// Řešení IJC-DU1, příklad b), 18.3.2024
// Autor: Petr Špác, FIT
// Přeloženo: gcc 11.4.0
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void warning(const char *fmt, ...) {

    va_list args;

    va_start(args, fmt);

    fprintf(stderr, "Warning: ");
    vfprintf(stderr, fmt, args);

    va_end(args);
}

void error_exit(const char *fmt, ...) {

    va_list args;

    va_start(args, fmt);

    fprintf(stderr, "Error: ");
    vfprintf(stderr, fmt, args);

    va_end(args);

    exit(1);
}
