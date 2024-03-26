COMPILER=gcc
FLAGS= -g -O2 -std=c11 -Wall -pedantic -Wextra

# Try to do the IVS wildcard thing 
tail: tail.c 
	$(COMPILER) $(FLAGS) tail.c -o tail

wordcount-: wordcount-.cc
	g++ -std=c++17 -pedantic -Wall wordcount-.cc

clear:
	rm *.o wordcount- wordcount tail



