#include "private_htab.h"

void htab_for_each(const htab_t *t, void (*f)(htab_pair_t *data)) {
    for (size_t i = 0; i < t->arr_size; i++) {
        struct htab_item *curr = t->p_arr[i];
        while (curr != NULL) {

            f(&curr->item);
            curr = curr->next;
        }
    }
}
