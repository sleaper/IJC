// htab_init.c
// Řešení IJC-DU2, příklad 2), 20.4.2024
// Autor: Petr Špác, FIT
// Přeloženo: gcc 11.4.0
#include "private_htab.h"
#include <stdio.h>
#include <stdlib.h>

htab *htab_init(const size_t n) {

    if (n == 0) {
        fprintf(stderr, "%s: Wrong number of arr_size!", __func__);
        return NULL;
    }

    size_t total_size = sizeof(htab) + n * sizeof(struct htab_item *);
    htab *t = malloc(total_size);
    if (t == NULL) {
        fprintf(stderr, "%s: No memory", __func__);
        return NULL;
    }

    t->arr_size = n;
    t->size = 0;

    // Initialize the array portion of the allocation to NULLs
    for (size_t i = 0; i < n; ++i) {
        t->p_arr[i] = NULL;
    }

    return t;
}
