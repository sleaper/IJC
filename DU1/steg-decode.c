#include "bitset.h"
#include "eratosthenes.h"
#include "error.h"
#include "ppm.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define START_PRIME 101

unsigned char *utf8_check(unsigned char *s);

int main(int argc, char **argv) {

    if (argc < 2) {
        error_exit("steg-decode: nespravny pocet argumentu\n");
    }

    struct ppm *image = ppm_read(argv[1]);
    if (image == NULL) {
        error_exit("steg-decode: chybny format\n");
    }

    unsigned long primes_len = 3 * image->xsize * image->ysize;

    bitset_alloc(primes, primes_len);
    Eratosthenes(primes);

    unsigned char *secret = malloc(primes_len / 8);
    if (secret == NULL) {
        bitset_free(primes);
        ppm_free(image);
        error_exit("steg-decode: nedostatek pameti");
    }

    char secret_char = 0;
    int bit_pos = 0;
    int end = 0;
    int secret_index = 0;

    for (unsigned long i = START_PRIME; i < primes_len; i++) {
        if (bitset_getbit(primes, i) == 0) {
            if (bit_pos == CHAR_BIT) {
                secret[secret_index++] = secret_char;

                if (secret_char == '\0') {
                    end = 1;
                    break;
                }

                bit_pos = 0;
                secret_char = 0;
            }

            // Get LSB and save to current char
            secret_char |= (image->data[i] & 1) << bit_pos++;
        }
    }

    if (utf8_check(secret)) {
        free(secret);
        error_exit("steg-decode: neni ve formatu UTF-8\n");
    }

    if (!end) {
        free(secret);
        error_exit("steg-decode: spatne ukonceni zpravy\n");
    }

    printf("%s\n", secret);

    bitset_free(primes);
    ppm_free(image);
    free(secret);
    return 0;
}

unsigned char *utf8_check(unsigned char *s) {
    while (*s) {
        if (*s < 0x80)
            /* 0xxxxxxx */
            s++;
        else if ((s[0] & 0xe0) == 0xc0) {
            /* 110XXXXx 10xxxxxx */
            if ((s[1] & 0xc0) != 0x80 || (s[0] & 0xfe) == 0xc0) /* overlong? */
                return s;
            else
                s += 2;
        } else if ((s[0] & 0xf0) == 0xe0) {
            /* 1110XXXX 10Xxxxxx 10xxxxxx */
            if ((s[1] & 0xc0) != 0x80 || (s[2] & 0xc0) != 0x80 ||
                (s[0] == 0xe0 && (s[1] & 0xe0) == 0x80) || /* overlong? */
                (s[0] == 0xed && (s[1] & 0xe0) == 0xa0) || /* surrogate? */
                (s[0] == 0xef && s[1] == 0xbf &&
                 (s[2] & 0xfe) == 0xbe)) /* U+FFFE or U+FFFF? */
                return s;
            else
                s += 3;
        } else if ((s[0] & 0xf8) == 0xf0) {
            /* 11110XXX 10XXxxxx 10xxxxxx 10xxxxxx */
            if ((s[1] & 0xc0) != 0x80 || (s[2] & 0xc0) != 0x80 ||
                (s[3] & 0xc0) != 0x80 ||
                (s[0] == 0xf0 && (s[1] & 0xf0) == 0x80) ||    /* overlong? */
                (s[0] == 0xf4 && s[1] > 0x8f) || s[0] > 0xf4) /* > U+10FFFF? */
                return s;
            else
                s += 4;
        } else
            return s;
    }

    return NULL;
}
