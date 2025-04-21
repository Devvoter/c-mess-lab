/*
*    Autor: Denys Pylypenko
*    Fakulta: FIT
*    IJC-DU2, zadani 1 b)
*    Soubor: htab_statistics.c
*    Datum: 23.4.2024
*/

#include <stdio.h>
#include "htab_private.h"

void htab_statistics(const htab_t *t) {
#ifdef STATISTICS
    fprintf(stderr, "Statistics for hash table:\n");
    for (size_t i = 0; i < t->arr_size; i++) {
        size_t chain_length = 0;
        for (htab_item_t *item = t->items[i]; item != NULL; item = item->next) {
            chain_length++;
        }
        fprintf(stderr, "Bucket %zu: %zu elements\n", i, chain_length);
    }
#else
    (void)t;
#endif
}
