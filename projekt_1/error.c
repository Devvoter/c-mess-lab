// error.c
// Řešení IJC-DU1, příklad b), 23.3.2024
// Autor: Denys Pylypenko, FIT
// Přeloženo: gcc 13.2.1

#include "error.h"

void warning(const char *fmt, ...) {
    va_list l;
    va_start(l, fmt);

    fprintf(stderr, "Warning: ");
    vfprintf(stderr, fmt, l);
    fprintf(stderr, "\n");

    va_end(l);
}

void error_exit(const char *fmt, ...) {
    va_list l;
    va_start(l, fmt);

    fprintf(stderr, "Error: ");
    vfprintf(stderr, fmt, l);
    fprintf(stderr, "\n");

    va_end(l);
    exit(EXIT_FAILURE);
}