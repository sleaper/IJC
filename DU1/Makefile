COMPILER=gcc
FLAGS= -g -O2 -std=c11 -Wall -pedantic -Wextra

all: primes primes-i steg-decode

run: all
	ulimit -s 35000; ./primes; ./primes-i; ./steg-decode du1-obrazek.ppm

# Macros
primes: primes.o error.o eratosthenes.o
	$(COMPILER) $(FLAGS) primes.o error.o eratosthenes.o -o primes -lm

primes.o: primes.c bitset.h eratosthenes.h
	$(COMPILER) $(FLAGS) -c primes.c -o primes.o

eratosthenes.o: eratosthenes.c eratosthenes.h bitset.h
	$(COMPILER) $(FLAGS) -c eratosthenes.c -o eratosthenes.o

# Inline functions
primes-i: primes-i.o bitset-i.o error.o eratosthenes-i.o
	$(COMPILER) $(FLAGS) primes-i.o bitset-i.o error.o eratosthenes-i.o -o primes-i -lm

primes-i.o: primes.c bitset.h eratosthenes.h
	$(COMPILER) $(FLAGS) -DUSE_INLINE -c primes.c -o primes-i.o

bitset-i.o: bitset.c bitset.h 
	$(COMPILER) $(FLAGS) -DUSE_INLINE -c bitset.c -o bitset-i.o

eratosthenes-i.o: eratosthenes.c eratosthenes.h bitset.h
	$(COMPILER) $(FLAGS) -DUSE_INLINE -c eratosthenes.c -o eratosthenes-i.o


error.o: error.c error.h 
	$(COMPILER) $(FLAGS) -c error.c -o error.o

steg-decode: steg-decode.c eratosthenes.c ppm.c error.h
	$(COMPILER) $(FLAGS) ppm.c error.c steg-decode.c eratosthenes.c -o steg-decode -lm

clean: clear

clear:
	rm *.o primes primes-i steg-decode
