// fileno declaration
#define _POSIX_C_SOURCE 200112L

#include "error.h"
#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    FILE *inputFile;
    FILE *outFile = stdout;

    int inDesc;
    int outDesc;

    struct stat fStat;
    struct stat oStat;

    if (argc == 2) {
        inputFile = fopen(argv[1], "r");
        if (!inputFile) {
            error_exit("no-comment: chyba otevreni souboru!\n");
        }

        inDesc = fileno(inputFile);
        outDesc = fileno(outFile);

        if (fstat(inDesc, &fStat) < 0)
            // TODO: Close file, maybe add goto
            return 1;

        if (fstat(outDesc, &oStat) < 0)
            return 1;

        if (oStat.st_ino == fStat.st_ino) {
            fclose(stdout);
            error_exit("no-comment: Stdout presmerovan na vstupni soubor!\n");
            return 1;
        }

    } else {
        inputFile = NULL;
    }

    int stav = 0;
    int c;

    while (inputFile != NULL ? (c = fgetc(inputFile)) != EOF
                             : (c = getchar()) != EOF) {
        switch (stav) {
        case 0:
            if (c == '/') {
                stav = 5;
            } else if (c == '"') {
                stav = 3;
                putchar(c);
            } else if (c == '\'') {
                stav = 1;
                putchar(c);
            } else {
                putchar(c);
            }
            break;
        case 1:
            if (c == '\'') {
                stav = 0;
                putchar(c);
            } else if (c == '\\') {
                stav = 2;
                putchar(c);
            } else {
                putchar(c);
            }
            break;
        case 2:
            stav = 1;
            putchar(c);
            break;
        case 3:
            if (c == '"') {
                stav = 0;
                putchar(c);
            } else if (c == '\\') {
                stav = 4;
                putchar(c);
            } else {
                putchar(c);
            }
            break;
        case 4:
            stav = 3;
            putchar(c);
            break;
        case 5:
            if (c == '*') {
                stav = 6;
            } else if (c == '/') {
                stav = 8;
            } else {
                stav = 0;
                putchar('/');
                putchar(c);
            }
            break;
        case 6:
            if (c == '*') {
                stav = 7;
            }
            break;
        case 7:
            if (c == '/') {
                stav = 0;
                putchar(' ');
            } else if (c != '*')
                stav = 6;
            break;
        case 8:
            if (c == '\\') {
                stav = 9;
            } else if (c == '\n') {
                stav = 0;
                putchar(c);
            }
            break;
        case 9:
            if (c != '\\') {
                stav = 8;
            }
            break;
        }
    }

    if (stav != 0)
        fprintf(stderr, "Error\n");

    if (inputFile) {
        fclose(inputFile);
    }

    return 0;
}
