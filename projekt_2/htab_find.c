/*
*    Autor: Denys Pylypenko
*    Fakulta: FIT
*    IJC-DU2, zadani 1 b)
*    Soubor: htab_find.c
*    Datum: 23.4.2024
*/

#include "htab_private.h"

htab_pair_t *htab_find(const htab_t *t, htab_key_t key) {
    // Vypocet indexu v poli retezcu
    size_t index = htab_hash_function(key) % t->arr_size;
    // Prochazime retezcem prvku pro tento index
    for (htab_item_t *item = t->items[index]; item != NULL; item = item->next) {
        if (strcmp(item->pair.key, key) == 0) {
            // Nasli jsme prvek, vracime ukazatel na par
            return &item->pair;
        }
    }
    // Prvek nenalezen, vracime NULL
    return NULL;
}
