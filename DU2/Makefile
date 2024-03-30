CC=gcc
CXX=g++

CFLAGS=-g -std=c11 -pedantic -Wall -Wextra -O0
CXXFLAGS=-std=c++17 -pedantic -Wall

LDFLAGS = -fPIC
# .PHONY=all test

all: tail test libhtab.a wordcount # wordcount-dynamic libhtab.so 

# FIRST TASK
tail: tail.o
	$(CC) -o $@ $^

tail.o: tail.c
	$(CC) $(CFLAGS) -c $< -o $@

# SECCOND TASK
wordcount: wordcount.o libhtab.a
	$(CC) $(CFLAGS) $^ -o $@ -L. -lhtab

wordcount.o: wordcount.c htab.h
	$(CC) $(CFLAGS) -c $< -o $@


test: test.o libhtab.a
	$(CC) $(CFLAGS) $^ -o $@ -L. -lhtab

test.o: test.c htab.h
	$(CC) $(CFLAGS) -c $< -o $@

# HTAB_LIBRARY
library_objects = htab_bucket_count.o htab_clear.o htab_erase.o htab_find.o htab_for_each.o htab_free.o htab_hash_function.o htab_init.o htab_lookup_add.o htab_size.o htab_statistics.o 
# TODO: DYnamic library

$(library_objects): %.o: %.c private_htab.h
	$(CC) $(CFLAGS) -c $< -o $@

libhtab.a: $(library_objects)
	ar -rcs $@ $^


wordcount-cc: wordcount-.cc
	g++ -O2 -o $@ $^

# test: test.c all wordcount-cc
# 	$(CC) $(CFLAGS) -o $@ $(LDFLAGS) $< libhtab.a
# 	bash test.sh

clear: clean

clean:
	rm -f *.o *.so *.a tail wordcount wordcountDynamic wordcountStatistic wordcount-cpp xspacpe00.zip
