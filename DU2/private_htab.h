// private_htab.h
// Řešení IJC-DU2, příklad 2), 20.4.2024
// Autor: Petr Špác, FIT
// Přeloženo: gcc 11.4.0

#ifdef DEBUG
#define DEBUG_PRINT(x) printf x
#else
#define DEBUG_PRINT(x)                                                         \
    do {                                                                       \
    } while (0)
#endif

#ifndef PRIVATE_HTAB_H__
#define PRIVATE_HTAB_H__
#include "htab.h" // IWYU pragma: export

struct htab_item {
    htab_pair_t item;
    struct htab_item *next;
};

typedef struct htab {
    size_t size;
    size_t arr_size;
    struct htab_item *p_arr[];
} htab;

#endif // PRIVATE_HTAB_H__
