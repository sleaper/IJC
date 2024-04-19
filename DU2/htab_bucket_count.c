// htab_bucket_count.c
// Řešení IJC-DU2, příklad 2), 20.4.2024
// Autor: Petr Špác, FIT
// Přeloženo: gcc 11.4.0
#include "private_htab.h"

size_t htab_bucket_count(const htab_t *t) { return t->arr_size; }
