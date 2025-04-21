// eratosthenes.c
// Řešení IJC-DU1, příklad a), 23.3.2024
// Autor: Denys Pylypenko, FIT
// Přeloženo: gcc 13.2.1

#include "eratosthenes.h" // bitset_t, bitset_index_t, bitset_setbit, bitset_size, bitset_getbit


void Eratosthenes(bitset_t pole) {
    bitset_index_t sqrt_pole = sqrt(bitset_size(pole));

    bitset_setbit(pole, 2, 1); // 2 je prvocislo
    // nastav vsechny liche cisla jako kandidaty prvocisel
    for (bitset_index_t i = 3; i < bitset_size(pole); i += 2) {
        bitset_setbit(pole, i, 1);
    }

    for (bitset_index_t i = 3; i < sqrt_pole; i += 2) {
        // odfiltruj vsechny nasobky prvocisla 'i'
        // (zacit muzeme od 'i * i', protoze vsechny predchozi nasobky 'i'
        // jsou jiz odfiltrovany predchozimi prvocisly)
        if (bitset_getbit(pole, i)){
            for (bitset_index_t j = i * i; j < bitset_size(pole); j += i + i) bitset_setbit(pole, j, 0);
        }
    }
}

