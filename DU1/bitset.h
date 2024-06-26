// bitset.h
// Řešení IJC-DU1, příklad a), 18.3.2024
// Autor: Petr Špác, FIT
// Přeloženo: gcc 11.4.0

#ifndef BITSET_H
#define BITSET_H

#include "assert.h"
#include "error.h"
#include "limits.h"
#include "string.h"

typedef unsigned long bitset_t[];
typedef unsigned long bitset_index_t;

// Define the size of an unsigned long in bits.
#define ULONG_SIZE (sizeof(unsigned long) * CHAR_BIT)

// Define number of ULONG for given number
#define BITSET_ULONG_POS(num) ((num) / ULONG_SIZE)

#define BIT_POS_IN_ULONG(num) ((num) % ULONG_SIZE)

#define BITSET_TOTAL_ULONGS(size)                                              \
    (BITSET_ULONG_POS(size) + (BIT_POS_IN_ULONG(size) ? 2 : 1))

// First element is size of the bitset
// 30bits = size[0 + 2] = [size, ulong]
// 64 = size[1 + 1] = [size, ulong]
// 100 = size[1 + 2] = [size, ulong, ulong]
#define bitset_create(jmeno_pole, velikost)                                    \
    unsigned long(jmeno_pole)[BITSET_TOTAL_ULONGS(velikost)] = {velikost};     \
    static_assert((velikost) > 0, "bitset_create: Pole musi byt vetsi nez 0")

#define bitset_alloc(jmeno_pole, velikost)                                     \
    assert((unsigned long)velikost < ULONG_MAX);                               \
    unsigned long *jmeno_pole =                                                \
        calloc((BITSET_TOTAL_ULONGS(velikost)), (sizeof(unsigned long)));      \
    if (jmeno_pole == NULL)                                                    \
        error_exit("bitset_alloc: Chyba lokace pameti");                       \
                                                                               \
    jmeno_pole[0] = velikost;

#define bitset_free(jmeno_pole) free(jmeno_pole);

#ifdef USE_INLINE

// Inline functions for bitset operations

inline unsigned long bitset_size(bitset_t jmeno_pole) { return jmeno_pole[0]; }

// Checks for index bounds and modifies the specified bit accordingly.
inline void bitset_setbit(bitset_t jmeno_pole, unsigned long index, int vyraz) {
    if (index >= bitset_size(jmeno_pole)) {
        error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu",
                   (unsigned long)index,
                   (unsigned long)bitset_size(jmeno_pole) - 1);
    }

    if (vyraz) {
        jmeno_pole[BITSET_ULONG_POS(index) + 1] |=
            (1UL << BIT_POS_IN_ULONG(index));
    } else {
        jmeno_pole[BITSET_ULONG_POS(index) + 1] &=
            ~(1UL << BIT_POS_IN_ULONG(index));
    }

    return;
}

inline unsigned long bitset_getbit(bitset_t jmeno_pole, unsigned long index) {
    if (index >= bitset_size(jmeno_pole)) {
        error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu",
                   (unsigned long)index,
                   (unsigned long)bitset_size(jmeno_pole) - 1);
    } else {
        return jmeno_pole[BITSET_ULONG_POS(index) + 1] &
                       (1UL << BIT_POS_IN_ULONG(index))
                   ? 1UL
                   : 0UL;
    }

    return 3;
}

inline void bitset_fill(bitset_t jmeno_pole, int bool_výraz) {
    if (bool_výraz) {
        for (unsigned long i = 1;
             i < BITSET_TOTAL_ULONGS(bitset_size(jmeno_pole)); i++) {
            jmeno_pole[i] = ULONG_MAX;
        }
    } else {
        for (unsigned long i = 1;
             (i) < (BITSET_TOTAL_ULONGS(bitset_size(jmeno_pole))); i++) {
            (jmeno_pole[i]) = 0;
        }
    }
}

#else

#define bitset_size(jmeno_pole) jmeno_pole[0]

#define bitset_setbit(jmeno_pole, index, vyraz)                                \
    if (((unsigned long)(index) >= (jmeno_pole[0])))                           \
        error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu",              \
                   (unsigned long)index,                                       \
                   (unsigned long)bitset_size(jmeno_pole) - 1);                \
    vyraz ? ((jmeno_pole[BITSET_ULONG_POS(index) + 1]) |=                      \
             (1UL << BIT_POS_IN_ULONG(index)))                                 \
          : ((jmeno_pole[BITSET_ULONG_POS(index) + 1]) &=                      \
             ~(1UL << BIT_POS_IN_ULONG(index)))

#define bitset_getbit(jmeno_pole, index)                                       \
    (((unsigned long)(index) >= bitset_size(jmeno_pole))                       \
         ? (error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu",          \
                       (unsigned long)index,                                   \
                       (unsigned long)bitset_size(jmeno_pole) - 1),            \
            3)                                                                 \
     : (jmeno_pole[BITSET_ULONG_POS(index) + 1] &                              \
        (1UL << BIT_POS_IN_ULONG(index)))                                      \
         ? 1UL                                                                 \
         : 0UL)

#define bitset_fill(jmeno_pole, bool_výraz)                                    \
    if (bool_výraz) {                                                          \
        for (unsigned long i = 1;                                              \
             (i) < (BITSET_TOTAL_ULONGS(bitset_size(jmeno_pole))); i++) {      \
            (jmeno_pole[i]) = ULONG_MAX;                                       \
        }                                                                      \
    } else {                                                                   \
        for (unsigned long i = 1;                                              \
             (i) < (BITSET_TOTAL_ULONGS(bitset_size(jmeno_pole))); i++) {      \
            (jmeno_pole[i]) = 0;                                               \
        }                                                                      \
    }

#endif

#endif
