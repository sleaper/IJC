// bitset.c
// Řešení IJC-DU1, příklad a), 18.3.2024
// Autor: Petr Špác, FIT
// Přeloženo: gcc 11.4.0
#ifdef USE_INLINE

#include "bitset.h"

extern inline unsigned long bitset_size(bitset_t jmeno_pole);
extern inline void bitset_setbit(bitset_t jmeno_pole, unsigned long index,
                                 int vyraz);
extern inline unsigned long bitset_getbit(bitset_t jmeno_pole,
                                          unsigned long index);
extern inline void bitset_fill(bitset_t jmeno_pole, int vyraz);

#endif
