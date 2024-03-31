#include "private_htab.h"
#include <stdio.h>
#include <stdlib.h>

bool htab_erase(htab_t *t, htab_key_t key) {

    int index = (htab_hash_function(key) % t->arr_size);

    struct htab_item *current = t->p_arr[index];

    if (current == NULL) {
        return false;
    }

    struct htab_item *prev = current;

    // Search for key
    while (current != NULL) {
        if (strcmp(current->item.key, key) == 0) {
            if (prev == current) {
                t->p_arr[index] = NULL;
            } else {
                prev->next = current->next;
            }

            DEBUG_PRINT(("DELETING: %s\n", key));
            // Delete the match
            free((char *)current->item.key);
            current->item.key = NULL; // dangling pointer
            free(current);

            t->size--;
            return true;
        }

        prev = current;
        current = current->next;
    }

    return false;
}
