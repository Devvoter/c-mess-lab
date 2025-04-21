/*
*    Autor: Denys Pylypenko
*    Fakulta: FIT
*    IJC-DU2, zadani 1 b)
*    Soubor: htab_clear.c
*    Datum: 23.4.2024
*/

#include "htab_private.h"
#include <stdlib.h>

void htab_clear(htab_t *t) {
    for (size_t i = 0; i < t->arr_size; i++) {
        htab_item_t *item = t->items[i];
        while (item != NULL) {
            htab_item_t *next = item->next;
            free((char *)item->pair.key); // Uvolneni pameti klice
            free(item); // Uvolneni pameti prvku
            item = next;
        }
        t->items[i] = NULL; // Nulovani ukazatele na zacatek seznamu
    }
    t->size = 0; // Nulovani velikosti tabulky
}
