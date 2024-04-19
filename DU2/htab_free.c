// htab_free.c
// Řešení IJC-DU2, příklad 2), 20.4.2024
// Autor: Petr Špác, FIT
// Přeloženo: gcc 11.4.0
#include "private_htab.h"
#include <stdlib.h>

void htab_free(htab_t *t) {
    if (t->size != 0) {
        htab_clear(t);
    }

    free(t);
}
