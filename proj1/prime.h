// CPSC2380
// Department of Computer Science, UALR
// Project 1
// Student Name: Connor Taffe
// Student UALR ID (last four digits): 3742
// Project Descriptions: (maximum 5 lines)
// This project is doing dynamic array expansion for storage of prime numbers.
// Project Due Date: 28/8/2014
// Project Revised Date: 4/9/2014

#include <cmath>
#include <new>
#import "array.h"

using namespace std;

// Atkin Sieve
Array *PrimeGen(Array *array, int min, int max) {
	int root = ceil(sqrt(max));
	const int sieve_size = (max - min) + 1;
	bool *sieve;
	try {
		sieve = new bool[sieve_size];
	} catch (std::bad_alloc& ba) {
		perror("PrimeGen new");
		return array;
	}

	// account for 3 & 2
	if (min < 2 && max >= 2) {array = ArrayPush(array, 2);}
	if (min < 3 && max >= 3) {array = ArrayPush(array, 3);}

	// init sieve w/ false
	for (int i = 0; i < sieve_size; i++) {
		sieve[i] = false;
	}

	// mark numbers as non-prime
	for (int x = 1; x <= root; x++) {
		for (int y = 1; y <= root; y++) {
			int n = (4 * x * x) + (y * y);
			if (n <= max && n > min && (n % 12 == 1 || n % 12 == 5)) {
					sieve[n - min] ^= true;
			}
			n = (3 * x * x) + (y * y);
			if (n <= max && n > min && n % 12 == 7) {
				if ((n-min) > 0 && (n-min) < (max - min)){
					sieve[n - min] ^= true;
				}
			}
			n = (3 * x * x) - (y * y);
			if (x > y && n <= max && n > min && n % 12 == 11) {
					sieve[n - min] ^= true;
			}
		}
	}

	//mark multiples of squares as non-prime
	for (int i = min; i <= root; i++) {
		if (sieve[i - min]) {
			for (int j = i * i; j < max; j += i * i) {
				sieve[j - min] = false;
			}
		}
	}

	// add primes to array
	for (int i = min; i <= max; i++) {
		if (sieve[i - min]) {
			array = ArrayPush(array, i);
		}
	}

	// get rid of sieve
	delete[] sieve;

	return array;
}