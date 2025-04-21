/*
*    Autor: Denys Pylypenko
*    Fakulta: FIT
*    IJC-DU2, zadani 1 b)
*    Soubor: wordcount.c
*    Datum: 24.4.2024
*/

#include <stdio.h>
#include <stdlib.h>
#include "htab_private.h"

#define MAX_WORD_LENGTH 255

void print_word_count(htab_pair_t *data) {
    printf("%s\t%d\n", data->key, data->value);
}

int main() {
    htab_t *table = htab_init(10000); // Inicializace tabulky
    if (table == NULL) {
        fprintf(stderr, "Chyba: Nelze vytvorit hash tabulku\n");
        return 1;
    }

    char word[MAX_WORD_LENGTH];
    while (scanf("%255s", word) == 1) { // Cteme slovo ze standardniho vstupu
        htab_pair_t *item = htab_lookup_add(table, word);
        if (item == NULL) {
            fprintf(stderr, "Chyba: Nelze pridat slovo do hash tabulky\n");
            htab_free(table);
            return 1;
        }
        item->value++;
    }

    #ifdef STATISTICS
    htab_statistics(table); // pokud chcete statistiku, zmnente pocet pro init na radku 20 pro overeni
    #endif


    // Vypiseme pocet kazdeho slova
    htab_for_each(table, print_word_count);
    
    htab_free(table); // Uvolnujeme zdroje
    return 0;
}
