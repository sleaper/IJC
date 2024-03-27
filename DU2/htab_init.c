#include "private_htab.h"
#include <stdio.h>
#include <stdlib.h>

htab *htab_init(const size_t n) {

    if (n == 0) {
        fprintf(stderr, "%s: Wrong number of arr_size!", __func__);
        return NULL;
    }

    htab *t = malloc(sizeof(htab));
    if (t == NULL) {
        fprintf(stderr, "%s: No memory", __func__);
        return NULL;
    }

    t->arr_size = n;
    t->size = 0;
    t->array = malloc(n * sizeof(struct htab_item));

    // Init all pointers
    for (int i = 0; i < n; i++) {
        t->array[i] = NULL;
    }

    return NULL;
}
