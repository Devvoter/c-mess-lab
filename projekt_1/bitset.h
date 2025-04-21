// bitset.h
// Řešení IJC-DU1, příklad a), 23.3.2024
// Autor: Denys Pylypenko, FIT
// Přeloženo: gcc 13.2.1

#ifndef _BITSET_H_
#define _BITSET_H_

#include <limits.h> // Pro CHAR_BIT a ULONG_MAX, dulezite konstanty
#include <stdlib.h> // Pro funkce calloc a free
#include <assert.h> // Pro makro assert
#include <stdbool.h> // pro bool
#include <math.h> // sqrt
#include <stdio.h> // printf, fprintf, stderr
#include <time.h> // clock_t, clock, CLOCKS_PER_SEC
#include "error.h"  // Funkce error_exit musi byt definovana v jinem souboru

// Typy pro praci s bitovymi poli
typedef unsigned long bitset_index_t;
typedef bitset_index_t *bitset_t;

// Pocet bitu na prvek typu unsigned long
#define BITS_PER_BITSET_ITEM (sizeof(bitset_index_t) * CHAR_BIT)

// Inline funkce pro zakladni operace s bitovymi poli
#ifdef USE_INLINE
// Uvolneni pameti bitoveho pole
static inline void bitset_free(bitset_t jmeno_pole) {
    free(jmeno_pole);
}

// Ziskani velikosti bitoveho pole
static inline bitset_index_t bitset_size(bitset_t jmeno_pole) {
    return jmeno_pole[0];
}

// Nastaveni hodnoty bitu
static inline void bitset_setbit(bitset_t jmeno_pole, bitset_index_t index, bool bool_vyraz) {
    if (index >= jmeno_pole[0]) {
        error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu", (unsigned long)index, (unsigned long)jmeno_pole[0] - 1);
    }
    if (bool_vyraz) {
        jmeno_pole[1 + index / BITS_PER_BITSET_ITEM] |= (1UL << (index % BITS_PER_BITSET_ITEM));
    } else {
        jmeno_pole[1 + index / BITS_PER_BITSET_ITEM] &= ~(1UL << (index % BITS_PER_BITSET_ITEM));
    }
}

static inline void bitset_fill(bitset_t jmeno_pole, bool bool_vyraz) {
    for (size_t i = 1; i <= (bitset_size(jmeno_pole) + BITS_PER_BITSET_ITEM - 1) / BITS_PER_BITSET_ITEM; ++i) {
        jmeno_pole[i] = bool_vyraz ? ~0UL : 0;
    }
}

// Ziskani hodnoty bitu
static inline bool bitset_getbit(bitset_t jmeno_pole, bitset_index_t index) {
    if (index >= jmeno_pole[0]) {
        error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu", (unsigned long)index, (unsigned long)jmeno_pole[0] - 1);
    }
    return (jmeno_pole[1 + index / BITS_PER_BITSET_ITEM] >> (index % BITS_PER_BITSET_ITEM)) & 1UL;
}

#else
// Definice zakladnich operaci s bitovymi poli pomoci maker
#define bitset_free(jmeno_pole) free(jmeno_pole)
#define bitset_size(jmeno_pole) (*(jmeno_pole))
#define bitset_setbit(jmeno_pole, index, bool_vyraz) do { \
    if ((index) >= jmeno_pole[0]) { \
        error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu", (unsigned long)(index), (unsigned long)jmeno_pole[0] - 1); \
    } \
    if (bool_vyraz) { \
        jmeno_pole[1 + (index) / BITS_PER_BITSET_ITEM] |= (1UL << ((index) % BITS_PER_BITSET_ITEM)); \
    } else { \
        jmeno_pole[1 + (index) / BITS_PER_BITSET_ITEM] &= ~(1UL << ((index) % BITS_PER_BITSET_ITEM)); \
    } \
} while (0)
#define bitset_getbit(jmeno_pole, index) \
    (((index) >= jmeno_pole[0]) \
        ? (error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu", (unsigned long)(index), (unsigned long)jmeno_pole[0] - 1), 0) \
        : (((jmeno_pole)[1 + (index) / BITS_PER_BITSET_ITEM] >> ((index) % BITS_PER_BITSET_ITEM)) & 1UL))
#endif

// Makra pro vytvoreni bitovych poli
#define bitset_create(jmeno_pole, velikost) \
    bitset_index_t jmeno_pole[((velikost) + BITS_PER_BITSET_ITEM - 1) / BITS_PER_BITSET_ITEM + 1] = { (velikost) }; \
    _Static_assert((velikost) > 0, "bitset_create: Velikost musi byt kladna")

#define bitset_alloc(jmeno_pole, velikost) do { \
    assert((velikost) > 0 && "bitset_alloc: Velikost musi byt kladna"); \
    jmeno_pole = (bitset_t)calloc(((velikost) + BITS_PER_BITSET_ITEM - 1) / BITS_PER_BITSET_ITEM + 1, sizeof(bitset_index_t)); \
    if (!(velikost)) { \
        fprintf(stderr, "bitset_alloc: Chyba alokace pameti\n"); \
        exit(EXIT_FAILURE); \
    } \
    *(jmeno_pole) = (velikost); \
} while (0)

#define bitset_fill(jmeno_pole, bool_vyraz) do { \
    for (size_t i = 1; i <= (bitset_size(jmeno_pole) + BITS_PER_BITSET_ITEM - 1) / BITS_PER_BITSET_ITEM; ++i) { \
        (jmeno_pole)[i] = (bool_vyraz) ? ~0UL : 0; \
    } \
} while (0)

#endif // konec _BITSET_H_
