// eratosthenes.c
// Řešení IJC-DU1, příklad a), 18.3.2024
// Autor: Petr Špác, FIT
// Přeloženo: gcc 11.4.0
#include "bitset.h"
#include <math.h>

void Eratosthenes(bitset_t pole) {

    unsigned long max = sqrt(pole[0]);

    bitset_fill(pole, 1);

    bitset_setbit(pole, 0, 0);
    bitset_setbit(pole, 1, 0);
    bitset_setbit(pole, 2, 1);

    // Skip even numbers
    for (unsigned long i = 3; i <= max; i += 2) {
        if (bitset_getbit(pole, i) == 1) {
            for (unsigned long j = i * i; j < bitset_size(pole); j += 2 * i) {
                bitset_setbit(pole, j, 0);
            }
        }
    }

    return;
}
