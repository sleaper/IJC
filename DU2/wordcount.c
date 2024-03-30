#include "htab.h"
#include "io.h"
#include <stdio.h>

#define MAX_WORD 255

int main(void) {

    // Create the hash table
    struct htab *table = htab_init(15);

    char word[MAX_WORD];

    // While and load words into hash table
    // Print all words from hash table
    htab_free(table);
    return 0;
}
