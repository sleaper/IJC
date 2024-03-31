CC=gcc
CXX=g++

CFLAGS=-g -std=c11 -pedantic -Wall -Wextra -O0
CXXFLAGS=-std=c++17 -pedantic -Wall

LDFLAGS = -fPIC
.PHONY=all test zip run

all: tail test libhtab.a libhtab.so wordcount wordcount-cc wordcount-dynamic

# FIRST TASK
tail: tail.o
	$(CC) -o $@ $^

tail.o: tail.c
	$(CC) $(CFLAGS) -c $< -o $@


# SECCOND TASK
# Wordcount
wordcount: wordcount.o io.o libhtab.a
	$(CC) $(CFLAGS) $^ -o $@

wordcount-dynamic: wordcount.o io.o libhtab.so
	$(CC) $(CFLAGS) $^ -o $@ -L. -lhtab -Bdynamic

wordcount.o: wordcount.c htab.h io.h
	$(CC) $(CFLAGS) -c $< -o $@

io.o: io.c
	$(CC) $(CFLAGS) -c $< -o $@

# TEST
test: test.o libhtab.a
	$(CC) $(CFLAGS) $^ -o $@ -L. -lhtab

test.o: test.c htab.h
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

run: wordcount wordcount-dynamic tail wordcount-cc
	seq 1000000 2000000|shuf > test.txt
	./tail < test.txt
	./wordcount < test.txt
	./wordcount-dynamic < test.txt
	./wordcount-cc < test.txt
	rm test.txt

clear: clean

clean:
	rm -f *.o *.so *.a tail wordcount wordcount-dynamic wordcount-cc xspacpe00.zip

zip:
	zip xnovot2p.zip *.c *.cc *.h makefile
