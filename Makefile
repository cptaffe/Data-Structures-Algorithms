CFLAGS=-O3
CC=clang++

primes:
	$(CC) $(CFLAGS) main.cpp -o primes

clean:
	rm primes