// primes.c
// Řešení IJC-DU1, příklad a), 18.3.2024
// Autor: Petr Špác, FIT
// Přeloženo: gcc 11.4.0
#include "bitset.h"
#include "eratosthenes.h"
#include <stdio.h>
#include <time.h>

#define N 666000000
#define LAST_TEN 10

int main(void) {

    clock_t start = clock();
    unsigned long nums[LAST_TEN] = {0};
    bitset_create(p, N);

    Eratosthenes(p);

    // Load last 10 prime numbers
    int count = 0;
    for (unsigned long i = bitset_size(p) - 1; count < LAST_TEN; i--) {
        if (bitset_getbit(p, i) == 1 && (i & 1UL) == 1) {
            nums[count++] = i;
        }
    }

    // Print last ten prime numbers
    for (int i = LAST_TEN - 1; i >= 0; i--) {
        printf("%lu\n", nums[i]);
    }

    fprintf(stderr, "Time=%.3g\n", (double)(clock() - start) / CLOCKS_PER_SEC);

    return 0;
}
