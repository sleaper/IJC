# Makefile
# Řešení IJC-DU2, příklad 1) + 2), 20.4.2024
# Autor: Petr Špác, FIT
CC=gcc
CXX=g++

CFLAGS=-g -std=c11 -pedantic -Wall -Wextra
CXXFLAGS=-std=c++17 -pedantic -Wall

LDFLAGS = -fPIC
.PHONY=all zip run clean

all: tail libhtab.a libhtab.so wordcount wordcount-cc wordcount-dynamic

# FIRST TASK
tail: tail.o
	$(CC) -o $@ $^

tail.o: tail.c
	$(CC) $(CFLAGS) -c $< -o $@

# SECCOND TASK
# Wordcount
wordcount: wordcount.o io.o libhtab.a
	$(CC) -o $@ $^ $(CFLAGS)

wordcount-dynamic: wordcount.o io.o libhtab.so
	$(CC) $(CFLAGS) $^ -o $@ -L. -lhtab -Bdynamic

wordcount.o: wordcount.c htab.h io.h
	$(CC) $(CFLAGS) -c $< -o $@

io.o: io.c
	$(CC) $(CFLAGS) -c $< -o $@

# Library files
source_files = htab_bucket_count.c htab_clear.c htab_erase.c htab_find.c htab_for_each.c htab_free.c htab_hash_function.c htab_init.c htab_lookup_add.c htab_size.c htab_statistics.c

obj_files = $(source_files:.c=.o)
dyn_obj_files = $(source_files:.c=-dyn.o)

# STATIC
$(obj_files): %.o: %.c private_htab.h
	$(CC) $(CFLAGS) -c $< -o $@

libhtab.a: $(obj_files)
	ar -rcs $@ $^

# DYNAMIC
$(dyn_obj_files): %-dyn.o: %.c private_htab.h
	$(CC) $(CFLAGS) $(LDFLAGS) -c $< -o $@

libhtab.so: $(dyn_obj_files)
	$(CC) $(LDFLAGS) -shared -o $@ $^  

wordcount-cc: wordcount-.cc
	$(CXX) $(CXXFLAGS) -o $@ $^


run: tail wordcount wordcount-cc wordcount-dynamic
	seq 1000000 2000000|shuf > tmp.txt
	./tail < tmp.txt
	./wordcount < tmp.txt
	LD_LIBRARY_PATH="." ./wordcount-dynamic < tmp.txt
	./wordcount-cc < tmp.txt
	rm tmp.txt

clear: clean

clean:
	rm -f *.o *.so *.a tail wordcount wordcount-dynamic wordcount-cc xspacpe00.zip

zip:
	zip xspacpe00.zip *.c *.cc *.h Makefile
