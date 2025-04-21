/*
*    Autor: Denys Pylypenko
*    Fakulta: FIT
*    IJC-DU2, zadani 1 b)
*    Soubor: htab_init.c
*    Datum: 23.4.2024
*/

#include "htab_private.h"
#include <stdlib.h>

htab_t *htab_init(size_t num) {
    htab_t *t = malloc(sizeof(htab_t));
    if (t == NULL) {
        return NULL; // Nepodarilo se vyhradit pamet pro tabulku
    }

    t->size = 0;
    t->arr_size = num;
    t->items = calloc(num, sizeof(htab_item_t *));
    if (t->items == NULL) {
        free(t);
        return NULL; // Nepodarilo se vyhradit pamet pro pole prvku
    }

    return t;
}
