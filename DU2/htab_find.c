// htab_find.c
// Řešení IJC-DU2, příklad 2), 20.4.2024
// Autor: Petr Špác, FIT
// Přeloženo: gcc 11.4.0
#include "private_htab.h"
#include <stdio.h>

htab_pair_t *htab_find(const htab_t *t, htab_key_t key) {

    int index = (htab_hash_function(key) % t->arr_size);
    DEBUG_PRINT(("finding: %s with index: %d\n", key, index));

    struct htab_item *current = t->p_arr[index];

    if (current == NULL) {
        DEBUG_PRINT(("DID NOT FIND %s\n", key));
        return NULL;
    }

    // Search for key
    while (current != NULL) {
        DEBUG_PRINT(("comapring %s, %s\n", current->item.key, key));
        if (strcmp(current->item.key, key) == 0) {
            return &current->item;
        }

        current = current->next;
    }

    return NULL;
}
