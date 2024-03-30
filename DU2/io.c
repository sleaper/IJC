#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

int read_word(char *s, int max, FILE *f) {
    if (f == NULL) {
        fprintf(stderr, "Error: could not work with file pointer!\n");
        return -1;
    }

    int c, len = 0;
    bool inword = false;
    while ((c = fgetc(f)) != EOF) {
        if (isspace(c)) {
            if (inword) {
                break;
            }
        } else if (!inword) {
            inword = true;
        }

        if (inword && len < max - 1) {
            s[len++] = (char)c;
        }
    }

    s[len] = '\0';

    if (c == EOF) {
        return EOF;
    }

    return len;
}
