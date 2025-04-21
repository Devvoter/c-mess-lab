CC=gcc
CFLAGS=-g -std=c11 -pedantic -Wall -Wextra -O3
LIB=-lm
ULIMIT=ulimit -s 100000


.PHONY: all clean run

all: primes primes-i no-comment


primes: primes.c bitset.h eratosthenes.c error.c error.h
	$(CC) $(CFLAGS) -o primes primes.c eratosthenes.c error.c $(LIB)

primes-i: CFLAGS+=-DUSE_INLINE
primes-i: primes.c bitset.h eratosthenes.c error.c error.h
	$(CC) $(CFLAGS) -o primes-i primes.c eratosthenes.c error.c $(LIB)

no-comment: no-comment.c error.c error.h
	$(CC) $(CFLAGS) -o no-comment no-comment.c error.c

run: all
	$(ULIMIT); ./primes; ./primes-i

clean:
	rm -f primes primes-i no-comment
