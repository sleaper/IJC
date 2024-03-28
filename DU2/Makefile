CC=gcc
CXX=g++

CFLAGS=-std=c11 -pedantic -Wall -Wextra -O2
CXXFLAGS=-std=c++17 -pedantic -Wall

LDFLAGS = -fPIC
# .PHONY=all test

all: tail libhtab.a #wordcount wordcount-dynamic libhtab.a libhtab.so 

# FIRST TASK
tail: tail.o
	$(CC) -o $@ $^

tail.o: tail.c
	$(CC) $(CFLAGS) -c $< -o $@

# SECCOND TASK
wordcount: wordcount.o
	$(CC) $(CFLAGS) $^ -o $@

wordcount.o: wordcount.c htab.h
	$(CC) $(CFLAGS) -c $< -o $@

# HTAB_LIBRARY
library_objects = htab_bucket_count.o htab_find.o htab_hash_function.o htab_size.o htab_lookup_add.o htab_init.o

libhtab.a: $(library_objects)
	ar -rcs $@ $^

$(library_objects): %.o: %.c private_htab.h
	$(CC) $(CFLAGS) -c $< -o $@

wordcount-cc: wordcount-.cc
	g++ -O2 -o $@ $^

# test: test.c all wordcount-cc
# 	$(CC) $(CFLAGS) -o $@ $(LDFLAGS) $< libhtab.a
# 	bash test.sh

clear: clean

clean:
	rm -f *.o *.so *.a tail wordcount wordcountDynamic wordcountStatistic wordcount-cpp xspacpe00.zip
