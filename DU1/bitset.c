#ifdef USE_INLINE

#include "bitset.h"

extern inline unsigned long bitset_size(bitset_t jmeno_pole);
extern inline void bitset_setbit(bitset_t jmeno_pole, unsigned long index,
                                 int vyraz);
extern inline unsigned long bitset_getbit(bitset_t jmeno_pole,
                                          unsigned long index);
extern inline void bitset_fill(bitset_t jmeno_pole, int vyraz);

#endif
