// htab_hash_function.c
// Řešení IJC-DU2, příklad 2), 20.4.2024
// Autor: Petr Špác, FIT
// Přeloženo: gcc 11.4.0
#include <stdint.h>
#include <string.h>

#ifdef MY_HASH_FUN_TEST

unsigned long hash(unsigned char *str) {
    unsigned int hash = 0;
    int c;

    while (c = *str++)
        hash += c;

    return hash;
}

#else

size_t htab_hash_function(const char *str) {
    uint32_t h = 0; // musí mít 32 bitů
    const unsigned char *p;
    for (p = (const unsigned char *)str; *p != '\0'; p++)
        h = 65599 * h + *p;
    return h;
}

#endif
