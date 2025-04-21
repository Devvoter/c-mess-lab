/*
*    Autor: Denys Pylypenko
*    Fakulta: FIT
*    IJC-DU2, zadani 1 b)
*    Soubor: htab_bucket_count.c
*    Datum: 23.4.2024
*/

#include "htab_private.h"

size_t htab_bucket_count(const htab_t * t){     // velikost pole

    return t->arr_size;

}