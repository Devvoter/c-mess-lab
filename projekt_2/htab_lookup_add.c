/*
*    Autor: Denys Pylypenko
*    Fakulta: FIT
*    IJC-DU2, zadani 1 b)
*    Soubor: htab_lookup_add.c
*    Datum: 23.4.2024
*/

#define _POSIX_C_SOURCE 200809L // pro funkci strdup
#include "htab_private.h"
#include <stdlib.h>
#include <string.h>

htab_pair_t *htab_lookup_add(htab_t *t, htab_key_t key) {
    
    htab_pair_t *tmp = htab_find(t, key);
    if (tmp != NULL)  return tmp;
    
    // Prvek nenalezen, vytvorime novy
    size_t index = htab_hash_function(key) % t->arr_size;
    htab_item_t *new_item = malloc(sizeof(htab_item_t));
    if (new_item == NULL) return NULL;  // Kontrola chyby pri vyhrazovani pameti

    // Vytvarime kopii klice
    char *key_copy = strdup(key);
    if (key_copy == NULL) {
        free(new_item);
        return NULL;
    }

    new_item->pair.key = key_copy;
    new_item->pair.value = 0;  // Pocatecni hodnota pocitadla
    new_item->next = t->items[index];  // Vkladame na zacatek seznamu
    t->items[index] = new_item;

    t->size++;  // Zvetsovani velikosti tabulky

    return &new_item->pair;
}
