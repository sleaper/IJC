#include "bitset.h"
#include <math.h>

void Eratosthenes(bitset_t pole) {

    unsigned long max = sqrt(pole[0]);

    bitset_setbit(pole, 0, 1);
    bitset_setbit(pole, 1, 1);

    for (unsigned long i = 2; i <= max; i++) {
        if (bitset_getbit(pole, i) == 0) {
            for (unsigned long j = i * i; j < bitset_size(pole); j += i) {
                bitset_setbit(pole, j, 1);
            }
        }
    }

    return;
}
