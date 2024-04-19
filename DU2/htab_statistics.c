// htab_statistics.c
// Řešení IJC-DU2, příklad 2), 20.4.2024
// Autor: Petr Špác, FIT
// Přeloženo: gcc 11.4.0

#include "private_htab.h"
#include <stdint.h>
#include <stdio.h>

void htab_statistics(const htab_t *t) {
    size_t max = 0;
    size_t min = SIZE_MAX;
    size_t all = 0;
    size_t curr_bucket_count = 0;

    for (size_t i = 0; i < t->arr_size; i++) {
        struct htab_item *head = t->p_arr[i];
        while (head != NULL) {
            curr_bucket_count++;
            head = head->next;
        }

        if (curr_bucket_count < min) {
            min = curr_bucket_count;
        }

        if (curr_bucket_count > max) {
            max = curr_bucket_count;
        }

        all += curr_bucket_count;
    }

    fprintf(stderr, "Max list len: %zu\n", max);
    fprintf(stderr, "Min list len: %zu\n", min);
    fprintf(stderr, "Avg list len: %f\n",
            (double)all / (double)htab_bucket_count(t));
}
