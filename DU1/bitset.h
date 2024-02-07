/** @file bitset.h
 *  @brief Macros and inline functions for bitset.
 *
 *  @author Petr Spac (xspacpe00)
 */

#ifndef BITSET_H
#define BITSET_H

#include "assert.h"
#include "error.h"
#include "limits.h"

typedef unsigned long *bitset_t;
typedef unsigned long bitset_index_t;

// Define the size of an unsigned long in bits.
#define ULONG_SIZE (sizeof(unsigned long) * CHAR_BIT)

#define BIT_POS_IN_ULONG(num) ((num) % ULONG_SIZE)

// Define number of ULONG for given number
#define BITSET_NUM_ULONGS(num) ((num) / ULONG_SIZE)

/**
 * @brief Macro for creating a bitset.
 *
 * @param jmeno_pole Name of the bitset variable.
 * @param velikost Size of the bitset.
 * @note This macro declares a bitset as an array of unsigned longs. The size is
 * specified by the user. It uses static assertion to ensure that the size is
 * greater than 0.
 */
#define bitset_create(jmeno_pole, velikost)                                    \
    unsigned long(jmeno_pole)[BITSET_NUM_ULONGS(velikost) +                    \
                              (BIT_POS_IN_ULONG(velikost) ? 2 : 1)] = {        \
        velikost};                                                             \
    static_assert((velikost) > 0, "bitset_create: Pole musi byt vetsi nez 0")

/**
 * Macro for dynamically allocating a bitset.
 *
 * @param jmeno_pole Name of the bitset variable.
 * @param velikost Size of the bitset.
 * @note This macro allocates memory for the bitset and initializes its size.
 *       It ensures that the size is less than ULONG_SIZE and handles memory
 * allocation errors.
 */
#define bitset_alloc(jmeno_pole, velikost)                                     \
    assert((unsigned long)velikost < ULONG_MAX);                               \
    unsigned long *jmeno_pole = calloc(                                        \
        (BITSET_NUM_ULONGS(velikost) + (BIT_POS_IN_ULONG(velikost) ? 2 : 1)),  \
        (sizeof(unsigned long)));                                              \
    if (jmeno_pole == NULL)                                                    \
        error_exit("bitset_alloc: Chyba lokace pameti");                       \
                                                                               \
    jmeno_pole[0] = velikost;

#define bitset_free(jmeno_pole) free(jmeno_pole);

#ifdef USE_INLINE

// Inline functions for bitset operations

inline unsigned long bitset_size(bitset_t jmeno_pole) { return jmeno_pole[0]; }

/**
 * Set or clear a bit in the bitset.
 *
 * @param jmeno_pole The bitset.
 * @param index Index of the bit to set or clear.
 * @param vyraz Non-zero to set the bit, zero to clear.
 * @note Checks for index bounds and modifies the specified bit accordingly.
 */
inline void bitset_setbit(bitset_t jmeno_pole, unsigned long index, int vyraz) {
    if (index >= bitset_size(jmeno_pole)) {
        error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu",
                   (unsigned long)index,
                   (unsigned long)bitset_size(jmeno_pole) - 1);
    }

    if (vyraz) {
        jmeno_pole[BITSET_NUM_ULONGS(index) + 1] |=
            (1UL << BIT_POS_IN_ULONG(index));
    } else {
        jmeno_pole[BITSET_NUM_ULONGS(index) + 1] &=
            ~(1UL << BIT_POS_IN_ULONG(index));
    }

    return;
}

/**
 * Get the value of a bit in the bitset.
 *
 * @param jmeno_pole The bitset.
 * @param index Index of the bit to retrieve.
 * @return Value of the bit at the specified index.
 * @note Checks for index bounds and returns the value of the specified bit.
 */
inline unsigned long bitset_getbit(bitset_t jmeno_pole, unsigned long index) {
    if (index >= bitset_size(jmeno_pole)) {
        error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu",
                   (unsigned long)index,
                   (unsigned long)bitset_size(jmeno_pole) - 1);
    } else {
        return jmeno_pole[BITSET_NUM_ULONGS(index) + 1] &
                       (1UL << BIT_POS_IN_ULONG(index))
                   ? 1UL
                   : 0UL;
    }

    return 3;
}

#else

#define bitset_size(jmeno_pole) jmeno_pole[0]

#define bitset_setbit(jmeno_pole, index, vyraz)                                \
    if (((unsigned long)(index) >= (jmeno_pole[0])))                           \
        error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu",              \
                   (unsigned long)index,                                       \
                   (unsigned long)bitset_size(jmeno_pole) - 1);                \
    vyraz ? ((jmeno_pole[BITSET_NUM_ULONGS(index) + 1]) |=                     \
             (1UL << BIT_POS_IN_ULONG(index)))                                 \
          : ((jmeno_pole[BITSET_NUM_ULONGS(index) + 1]) &=                     \
             ~(1UL << BIT_POS_IN_ULONG(index)))

#define bitset_getbit(jmeno_pole, index)                                       \
    (((unsigned long)(index) >= bitset_size(jmeno_pole))                       \
         ? (error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu",          \
                       (unsigned long)index,                                   \
                       (unsigned long)bitset_size(jmeno_pole) - 1),            \
            3)                                                                 \
     : (jmeno_pole[BITSET_NUM_ULONGS(index) + 1] &                             \
        (1UL << BIT_POS_IN_ULONG(index)))                                      \
         ? 1UL                                                                 \
         : 0UL)

#endif

#endif
