// WARNING: TRY on merlin maybe just
#define _POSIX_C_SOURCE 200809L
#include "private_htab.h"
#include <stdio.h>
#include <stdlib.h>
// key = string, value = pocet vyskytu

struct htab_item *create_item(htab_key_t key) {
    struct htab_item *new_item = malloc(sizeof(struct htab_item));
    if (new_item == NULL) {
        fprintf(stderr, "%s, no memory pair", __func__);
        return NULL;
    }
    new_item->item.key = NULL;
    new_item->item.value = 0;
    new_item->next = NULL;

    char *string = strdup(key);
    if (string == NULL) {
        fprintf(stderr, "%s, error copying a key", __func__);
        return NULL;
    }

    new_item->item.key = string;
    // WARNING: Maybe remove? It will be done by user?
    // new_item->item.value++;

    return new_item;
}

htab_pair_t *htab_lookup_add(htab_t *t, htab_key_t key) {

    htab_pair_t *current = htab_find(t, key);

    if (current) {
        return current;
    } else {
        DEBUG_PRINT(("ADDING: %s\n", key));
        int index = (htab_hash_function(key) % t->arr_size);

        struct htab_item *new_item = create_item(key);

        new_item->next = t->p_arr[index];
        t->p_arr[index] = new_item;
        t->size++;

        return &t->p_arr[index]->item;
    }
}
