#include "private_htab.h"
#include <stdlib.h>

void htab_free(htab_t *t) {
    if (t->size != 0) {
        htab_clear(t);
    }

    free(t);
}
