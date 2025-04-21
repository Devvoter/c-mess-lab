/*
*    Autor: Denys Pylypenko
*    Fakulta: FIT
*    IJC-DU2, zadani 1 b)
*    Soubor: htab_hash_function.c
*    Datum: 22.4.2024
*/

#include <inttypes.h> 
#include "htab_private.h"

// Standardni funkce hasirovani (sdbm)
size_t sdbm_hash_function(const char *str) {
    uint32_t h = 0; // musi byt 32 bitu
    const unsigned char *p;
    for (p = (const unsigned char*)str; *p != '\0'; p++)
        h = 65599 * h + *p;
    return h;
}

// Nova funkce hasirovani (djb2)
size_t djb2_hash_function(const char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash;
}

// Vyber funkce hasirovani v zavislosti na definici HASH_FUN_
#ifdef SDBM_HASH_FUN_
size_t htab_hash_function(const char *str) {
    return sdbm_hash_function(str);
}
#else
size_t htab_hash_function(const char *str) {
    return djb2_hash_function(str);
}
#endif
