// Filename: test.c
// Author: Tomas Brablec (xbrabl04)
// Faculty: FIT BUT
// Date: 2023-03-28

#include "htab.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

// #define STATISTICS

// this is a 'dirty code' - freeing is optional
void test_lookup_add() {
    htab_t *htab = htab_init(1000);
    htab_pair_t *new = htab_lookup_add(htab, "kentus");
    new->value = 42;
    htab_pair_t *exist = htab_lookup_add(htab, "kentus");
    assert(strcmp(exist->key, "kentus") == 0);
    assert(exist->value == 42);

    htab_free(htab);
}

bool found = false;
void find42(htab_pair_t *pair) {
    if (strcmp(pair->key, "kentus") == 0 && pair->value == 42)
        found = true;
}

int even_count = 0;
void is_even(htab_pair_t *pair) {
    if ((pair->value & 1) != 1) {
        even_count++;
    }
}

static int entry_count = 0;
static int value_sum = 0;

// Test function to count entries
void count_entries(htab_pair_t *data) {
    (void)data; // Unused parameter
    entry_count++;
}

// Test function to sum up the values
void sum_values(htab_pair_t *data) { value_sum += data->value; }

void test_foreach() {
    htab_t *htab = htab_init(1000);
    htab_lookup_add(htab, "kentus")->value = 42;
    htab_lookup_add(htab, "petr")->value = 1;
    htab_lookup_add(htab, "pepa")->value = 2;
    htab_lookup_add(htab, "petra")->value = 4;
    htab_lookup_add(htab, "apple")->value = 1;
    htab_lookup_add(htab, "banana")->value = 2;
    htab_lookup_add(htab, "cherry")->value = 3;

    htab_for_each(htab, find42);
    assert(found);

    htab_for_each(htab, is_even);
    assert(even_count == 4);

    htab_for_each(htab, count_entries);
    assert(entry_count == 7);

    htab_for_each(htab, sum_values);
    assert(value_sum == 55);

    htab_free(htab);
}

void test_bucket_count() {
    htab_t *htab = htab_init(1000);
    assert(htab_bucket_count(htab) == 1000);

    htab_free(htab);
}

void test_erase() {
    htab_t *htab = htab_init(1000);
    htab_lookup_add(htab, "kentus")->value = 42;
    assert(htab_erase(htab, "kentus") == true);
    assert(htab_erase(htab, "blentus") == false);

    htab_free(htab);
}

void test_erase_2() {
    htab_t *htab = htab_init(1000);
    htab_lookup_add(htab, "kentus")->value = 42;
    htab_lookup_add(htab, "blentus")->value = 666;

    assert(htab_erase(htab, "kentus") == true);
    assert(htab_erase(htab, "blentus") == true);

    assert(htab_find(htab, "kentus") == NULL);
    assert(htab_find(htab, "blentus") == NULL);

    htab_free(htab);
}

void test_find() {
    htab_t *htab = htab_init(1000);
    htab_lookup_add(htab, "kentus")->value = 42;
    assert(strcmp(htab_find(htab, "kentus")->key, "kentus") == 0);
    assert(htab_find(htab, "kentus")->value == 42);
    assert(htab_find(htab, "blentus") == NULL);

    htab_free(htab);
}

void test_clear() {
    htab_t *htab = htab_init(1000);
    htab_lookup_add(htab, "kentus")->value = 42;
    htab_clear(htab);
    assert(htab_find(htab, "kentus") == NULL);

    htab_free(htab);
}

void test_collision_2() {
    htab_t *htab = htab_init(1);
    htab_lookup_add(htab, "kentus")->value = 42;
    htab_lookup_add(htab, "blentus")->value = 666;

    assert(htab_find(htab, "kentus")->value == 42);
    assert(htab_find(htab, "blentus")->value == 666);

    htab_free(htab);
}

void test_collision_3() {
    htab_t *htab = htab_init(1);
    htab_lookup_add(htab, "kentus")->value = 42;
    htab_lookup_add(htab, "blentus")->value = 666;
    htab_lookup_add(htab, "mentus")->value = -1;

    assert(htab_find(htab, "kentus")->value == 42);
    assert(htab_find(htab, "blentus")->value == 666);
    assert(htab_find(htab, "mentus")->value == -1);

    htab_free(htab);
}

void test_collision_many() {
    htab_t *htab = htab_init(3);
    htab_lookup_add(htab, "kentus")->value = 42;
    htab_lookup_add(htab, "blentus")->value = 666;
    htab_lookup_add(htab, "mentus")->value = -1;
    htab_lookup_add(htab, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\njahawdh "
                          "!##$@%#^%^&$&*&^^&**()_+_+{{}}|:\"L?>><><")
        ->value = 45;
    htab_lookup_add(htab, "")->value = 98;
    htab_lookup_add(htab, "<fill in later>")->value = 0x1f595;
    htab_lookup_add(htab, "🖖")->value = 0x1f596;
    htab_lookup_add(htab, "co mam sakra furt vymyslet, tohle by za me melo "
                          "psat chatgpt takovyhle boilerplaty")
        ->value = 1;
    htab_lookup_add(htab, "no konecne")->value = 0;

    assert(htab_find(htab, "kentus")->value == 42);
    assert(htab_find(htab, "blentus")->value == 666);
    assert(htab_find(htab, "mentus")->value == -1);
    assert(htab_find(htab, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\njahawdh "
                           "!##$@%#^%^&$&*&^^&**()_+_+{{}}|:\"L?>><><")
               ->value == 45);
    assert(htab_find(htab, "")->value == 98);
    assert(htab_find(htab, "<fill in later>")->value == 0x1f595);
    assert(htab_find(htab, "🖖")->value == 0x1f596);
    assert(htab_find(htab, "co mam sakra furt vymyslet, tohle by za me melo "
                           "psat chatgpt takovyhle boilerplaty")
               ->value == 1);
    assert(htab_find(htab, "no konecne")->value == 0);

    assert(htab_find(htab, "neco vice") == NULL);

    htab_free(htab);
}

void test_size() {
    htab_t *htab = htab_init(1);
    assert(htab_size(htab) == 0);

    htab_lookup_add(htab, "kentus")->value = 42;
    assert(htab_size(htab) == 1);

    htab_lookup_add(htab, "blentus")->value = 666;
    assert(htab_size(htab) == 2);

    htab_erase(htab, "kentus");
    assert(htab_size(htab) == 1);

    htab_clear(htab);
    assert(htab_size(htab) == 0);

    htab_free(htab);
}

#ifdef STATISTICS
void test_statistics() {
    htab_t *htab = htab_init(5);
    htab_lookup_add(htab, "kentus")->value = 42;
    htab_lookup_add(htab, "petr")->value = 1;
    htab_lookup_add(htab, "pepa")->value = 2;
    htab_lookup_add(htab, "petra")->value = 4;
    htab_lookup_add(htab, "apple")->value = 1;
    htab_lookup_add(htab, "banana")->value = 2;
    htab_lookup_add(htab, "cherry")->value = 3;
    htab_lookup_add(htab, "kentus")->value = 42;
    htab_lookup_add(htab, "blentus")->value = 666;
    htab_lookup_add(htab, "mentus")->value = -1;
    htab_lookup_add(htab, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\njahawdh "
                          "!##$@%#^%^&$&*&^^&**()_+_+{{}}|:\"L?>><><");

    printf("ATTENTION: You should probably take a look at this: \n");
    htab_statistics(htab);

    htab_free(htab);
}
#endif // STATISTICS

int main() {
    // test_lookup_add();
    // test_foreach();
    // test_bucket_count();
    // test_erase();
    // test_find();
    // test_clear();
    // test_collision_2();
    // test_collision_3();
    // test_collision_many();
    // test_size();
#ifdef STATISTICS
    test_statistics();
#endif // STATISTICS

    return 0;
}
