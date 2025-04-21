/*
*    Autor: Denys Pylypenko
*    Fakulta: FIT
*    IJC-DU2, zadani 1 b)
*    Soubor: htab_size.c
*    Datum: 23.4.2024
*/

#include "htab_private.h"

size_t htab_size(const htab_t * t){             // počet záznamů v tabulce

    return t->size;
}