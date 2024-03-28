#ifndef PRIVATE_HTAB_H__
#define PRIVATE_HTAB_H__
#include "htab.h" // IWYU pragma: export

struct htab_item {
    htab_pair_t *item;
    struct htab_item *next;
};

typedef struct htab {
    size_t size;
    size_t arr_size;
    struct htab_item *p_arr[];
} htab;

#endif // PRIVATE_HTAB_H__
