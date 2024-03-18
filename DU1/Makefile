# Makefile
# Řešení IJC-DU1, 18.3.2024
# Autor: Petr Špác, FIT
COMPILER=gcc
FLAGS= -g -O2 -std=c11 -Wall -pedantic -Wextra

all: primes primes-i no-comment

run: all
	ulimit -s 85000; ./primes; ./primes-i;

# Macros
primes: primes.o error.o eratosthenes.o
	$(COMPILER) $(FLAGS) primes.o error.o eratosthenes.o -o primes -lm

primes.o: primes.c bitset.h error.h eratosthenes.h
	$(COMPILER) $(FLAGS) -c primes.c -o primes.o

eratosthenes.o: eratosthenes.c bitset.h error.h
	$(COMPILER) $(FLAGS) -c eratosthenes.c -o eratosthenes.o

# Inline functions
primes-i: primes-i.o bitset-i.o error.o eratosthenes-i.o
	$(COMPILER) $(FLAGS) primes-i.o bitset-i.o error.o eratosthenes-i.o -o primes-i -lm

primes-i.o: primes.c bitset.h error.h eratosthenes.h
	$(COMPILER) $(FLAGS) -DUSE_INLINE -c primes.c -o primes-i.o

bitset-i.o: bitset.c bitset.h error.h
	$(COMPILER) $(FLAGS) -DUSE_INLINE -c bitset.c -o bitset-i.o

eratosthenes-i.o: eratosthenes.c bitset.h error.h
	$(COMPILER) $(FLAGS) -DUSE_INLINE -c eratosthenes.c -o eratosthenes-i.o

error.o: error.c error.h 
	$(COMPILER) $(FLAGS) -c error.c -o error.o

# TASK 2
no-comment: no-comment.o error.o
	$(COMPILER) $(FLAGS) no-comment.o error.o -o no-comment

no-comment.o: no-comment.c error.h
	$(COMPILER) $(FLAGS) -c no-comment.c -o no-comment.o

clean: clear

clear:
	rm *.o primes primes-i no-comment
