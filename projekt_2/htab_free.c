/*
*    Autor: Denys Pylypenko
*    Fakulta: FIT
*    IJC-DU2, zadani 1 b)
*    Soubor: htab_free.c
*    Datum: 23.4.2024
*/

#include "htab_private.h"
#include <stdlib.h>

void htab_free(htab_t *t) {
    htab_clear(t); // Nejprve vycistime vsechny prvky
    free(t->items); // Uvolneni pole ukazatelu
    free(t); // Uvolneni samotne struktury tabulky
}
