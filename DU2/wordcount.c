#include "htab.h"
#include <stdio.h>

int main(void) {

    // Create the hash table
    struct htab *table = htab_init(10);

    // Add some word
    htab_pair_t *item = htab_lookup_add(table, "petr");

    printf("key: %s, value: %d", item->key, item->value);
    // While and load words into hash table
    // Print all words from hash table

    return 0;
}
