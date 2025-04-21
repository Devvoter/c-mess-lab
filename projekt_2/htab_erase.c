/*
*    Autor: Denys Pylypenko
*    Fakulta: FIT
*    IJC-DU2, zadani 1 b)
*    Soubor: htab_erase.c
*    Datum: 23.4.2024
*/

#include "htab_private.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool htab_erase(htab_t *t, htab_key_t key) {
    size_t index = htab_hash_function(key) % t->arr_size;
    htab_item_t *item = t->items[index];
    htab_item_t *prev_item = NULL;

    // Prochazime seznamem pro dany index
    while (item != NULL) {
        if (strcmp(item->pair.key, key) == 0) {
            // Pokud je prvek nalezen
            if (prev_item == NULL) {
                // Prvek se nachazi na zacatku seznamu
                t->items[index] = item->next;
            } else {
                // Prvek se nachazi ve stredu nebo na konci seznamu
                prev_item->next = item->next;
            }

            // Uvolnujeme pamet, zaberanou klicem a samotnym prvkem
            free((char *)item->pair.key); // uvolnujeme pamet vyhrazenou pro klic
            free(item); // uvolnujeme pamet vyhrazenou pro prvek
            t->size--; // snizujeme velikost hash tabulky
            return true;
        }
        prev_item = item;
        item = item->next;
    }

    // Prvek s danym klicem nebyl nalezen
    return false;
}
