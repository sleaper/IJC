#include "private_htab.h"
#include <stdlib.h>

void htab_clear(htab_t *t) {
    // For every linked list
    for (size_t i = 0; i < t->arr_size; i++) {
        struct htab_item *head = t->p_arr[i];
        struct htab_item *tmp = NULL;
        while (head != NULL) {
            tmp = head;
            head = head->next;

            // Free item
            free((char *)tmp->item.key);
            tmp->item.key = NULL; // dangling pointer
            free(tmp);

            t->size--;
        }

        t->p_arr[i] = NULL; // dangling pointer
    }
}
