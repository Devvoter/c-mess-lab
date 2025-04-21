/*
*    Autor: Denys Pylypenko
*    Fakulta: FIT
*    IJC-DU2, zadani 1 b)
*    Soubor: htab_private.h
*    Datum: 23.4.2024
*/

#ifndef HTAB_PRIVATE_H
#define HTAB_PRIVATE_H

#include "htab.h" // Verejny hlavickovy soubor

typedef struct htab_item {
    struct htab_item *next;  // ukazatel na dalsi prvek
    htab_pair_t pair;        // par klic-hodnota
} htab_item_t;

struct htab {
    size_t size;         // aktualni pocet prvku
    size_t arr_size;     // velikost pole
    htab_item_t **items; // pole ukazatelu na prvky
};

#endif // HTAB_PRIVATE_H
