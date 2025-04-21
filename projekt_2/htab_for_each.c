/*
*    Autor: Denys Pylypenko
*    Fakulta: FIT
*    IJC-DU2, zadani 1 b)
*    Soubor: htab_for_each.c
*    Datum: 23.4.2024
*/
#include "htab_private.h"

void htab_for_each(const htab_t *t, void (*f)(htab_pair_t *data)) {
    for (size_t i = 0; i < t->arr_size; i++) {
        for (htab_item_t *item = t->items[i]; item != NULL; item = item->next) {
            f(&item->pair);  // Volani funkce pro kazdy par
        }
    }
}
