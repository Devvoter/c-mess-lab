// error.h
// Řešení IJC-DU1, příklad b), 23.3.2024
// Autor: Denys Pylypenko, FIT
// Přeloženo: gcc 13.2.1

#ifndef _ERROR_H_
#define _ERROR_H_

#include <stdio.h> // vfprintf, stderr
#include <stdarg.h> // va_list, va_start, va_end
#include <stdlib.h> // exit, EXIT_FAILURE

void warning(const char *fmt, ...);
void error_exit(const char *fmt, ...);

#endif // _ERROR_H_
