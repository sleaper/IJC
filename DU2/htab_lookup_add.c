#include "private_htab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// key = string, value = pocet vyskytu

struct htab_item *create_item(htab_key_t key) {

    struct htab_item *new_item = malloc(sizeof(struct htab_item));
    if (new_item == NULL) {
        fprintf(stderr, "%s, no memory pair", __func__);
        return NULL;
    }

    char *new_string = malloc(strlen(key) + 1);
    if (new_item->item->key == NULL) {
        fprintf(stderr, "%s, no memory for new string", __func__);
        return NULL;
    }
    strcpy(new_string, key);

    new_item->item->key = new_string;
    new_item->next = NULL;

    return new_item;
}

htab_pair_t *htab_lookup_add(htab_t *t, htab_key_t key) {

    int index = (htab_hash_function(key) % t->arr_size);

    struct htab_item *current = t->p_arr[index];

    if (current == NULL) {
        t->p_arr[index] = create_item(key);

        return t->p_arr[index]->item;

    } else {

        // Search for key
        while (current->next != NULL) {
            if (strcmp(current->item->key, key) == 0) {
                return current->item;
            }

            current = current->next;
        }

        struct htab_item *new_item = create_item(key);
        new_item->next = t->p_arr[index];
        t->p_arr[index] = new_item;

        return t->p_arr[index]->item;
    }
}
