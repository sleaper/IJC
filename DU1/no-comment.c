#include "error.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    FILE *pFile;

    if (argc == 2) {
        pFile = fopen(argv[1], "r");

        if (!pFile) {
            error_exit("no-comment: chyba otevreni souboru!\n");
        }
    } else {
        pFile = NULL;
    }

    int stav = 0;
    int c;

    while (pFile != NULL ? (c = fgetc(pFile)) != EOF : (c = getchar()) != EOF) {
        switch (stav) {
        case 0:
            if (c == '/') {
                stav = 1;
            } else if (c == '"') {
                stav = 6;
                putchar(c);
            } else if (c == '\'') {
                stav = 8;
                putchar(c);
            } else {
                putchar(c);
            }
            break;
        case 1:
            if (c == '*') {
                stav = 4;
            } else if (c == '/') {
                stav = 2;
            } else {
                stav = 0;
                putchar('/');
                putchar(c);
            }
            break;
        case 2:
            if (c == '\\') {
                stav = 3;
            } else if (c == '\n') {
                stav = 0;
                putchar(c);
            } else {
                putchar(c);
            }
            break;
        case 3:
            if (c != '\n') {
                stav = 2;
            }
            break;
        case 4:
            if (c == '*') {
                stav = 5;
            }
            break;
        case 5:
            if (c == '/') {
                stav = 0;
                putchar(' ');
            } else if (c != '*')
                stav = 2;
            break;
        case 6:
            if (c == '"') {
                stav = 0;
                putchar(c);
            } else if (c == '\\') {
                stav = 7;
                putchar(c);
            } else {
                putchar(c);
            }
            break;
        case 7:
            stav = 6;
            putchar(c);
            break;
        case 8:
            if (c == '\'') {
                stav = 0;
                putchar(c);
            } else if (c == '\\') {
                stav = 9;
                putchar(c);
            } else {
                putchar(c);
            }
            break;
        case 9:
            stav = 8;
            putchar(c);
            break;
        }
    }

    if (stav != 0)
        fprintf(stderr, "Error\n");

    return 0;
}
