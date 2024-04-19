// wordcount.c
// Řešení IJC-DU2, příklad 2), 20.4.2024
// Autor: Petr Špác, FIT
// Přeloženo: gcc 11.4.0

#include "htab.h"
#include "io.h"
#include <stdio.h>

#define MAX_WORD 255
#define MAX_BUF (MAX_WORD + 2)

void print_pair(htab_pair_t *data) {
    printf("%s\t%d\n", data->key, data->value);
}

int main(void) {
    struct htab *table = htab_init(
        10000); // Velikost zavisi na vstupnim souboru. Vybral jsem 10000, aby
                // seq 1000000 2000000|shuf trval na Merlinovi pod 10s

    char word[MAX_BUF];
    int error = 0;
    while (read_word(word, MAX_BUF, stdin) != EOF) {
        if (strlen(word) > MAX_WORD && error == 0) {
            fprintf(stderr, "%s: Slovo zkraceno.\n", __func__);
            error = 1;
        }

        if (strlen(word) > MAX_WORD) {
            word[MAX_WORD] = '\0';
        }

        htab_pair_t *item = htab_lookup_add(table, word);
        if (item == NULL) {
            fprintf(stderr, "%s: Nepodarilo se pridat slovo do tabulky.\n",
                    __func__);
            htab_free(table);
            return 1;
        }
        item->value++;
    }

    htab_for_each(table, print_pair);

#ifdef STATISTICS
    htab_statistics(table);
#endif

    htab_free(table);
    return 0;
}
