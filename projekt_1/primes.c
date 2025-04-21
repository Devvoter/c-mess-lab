// primes.c
// Řešení IJC-DU1, příklad a), 23.3.2024
// Autor: Denys Pylypenko, FIT
// Přeloženo: gcc 13.2.1

#include "eratosthenes.h" // eratosthenes

int main(void) {
    clock_t start = clock();

    bitset_create(pole, 666000000); 

    Eratosthenes(pole);

    // ziskavame index 10. prvocisla od konce
    bitset_index_t index = bitset_size(pole) - 1;
    for (int counter = 0; counter < 10; --index) 
        counter += (bitset_getbit(pole, index)); // kontrola jestli je prvocislo
        
    // print poslednich 10 prvocisel
    index++;
    while(index < bitset_size(pole)) {
        if (bitset_getbit(pole, index)) printf("%lu\n", index);
        index++;
    }

    fprintf(stderr, "Time=%.3g\n", (double)(clock() - start) / CLOCKS_PER_SEC);
}

