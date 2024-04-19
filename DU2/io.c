// io.c
// Řešení IJC-DU2, příklad 2), 20.4.2024
// Autor: Petr Špác, FIT
// Přeloženo: gcc 11.4.0

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

void skip(FILE *file) {
    int c;
    while (c = fgetc(file), !isspace(c) && c != EOF)
        ;
    return;
}

int read_word(char *s, int max, FILE *f) {
    if (f == NULL) {
        fprintf(stderr, "%s: Neplatny ukazatel na soubor!\n", __func__);
        return -1;
    }

    int c, len = 0;
    bool isWordStarted = false;
    while ((c = fgetc(f)) != EOF) {
        if (!isspace(c) && len < max - 1) {
            s[len++] = (char)c;
            isWordStarted = true;
        } else if (isspace(c) && isWordStarted) {
            break;
        } else if (len >= max - 1) {
            skip(f);
            break;
        }
    }

    s[len] = '\0';

    if (len == 0 && c == EOF) {
        return EOF;
    }

    return len;
}
