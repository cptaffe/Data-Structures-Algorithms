// Extra Credit for Data Structures & Algorithms

// Get all prime numbers between a max and zero,
// realloc for larger and smaller numbers, filling
// in all of the positions with prime numbers.

#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>

using namespace std;

typedef struct {
	void *link;
	int data;
} List;

List *listLink(List *list, int item) {
	List *new_list = new List;
	new_list->data = item;
	new_list->link = NULL;
	list->link = new_list;
	return new_list;
}

List *atkinSievePrimeGen(List *list, int min, int max) {
	//Create the various different variables required
	int root = ceil(sqrt(max));
	bool sieve[max - min];

	for (int i = 0; i < (max - min); i++) {
		sieve[i] = false;
	}

	for (int x = 1; x <= root; x++) {
		for (int y = 1; y <= root; y++) {
			int n = (4 * x * x) + (y * y);
			if (n <= max && (n % 12 == 1 || n % 12 == 5)) {
				sieve[n - min] ^= true;
			}
			n = (3 * x * x) + (y * y);
			if (n <= max && n % 12 == 7) {
				sieve[n - min] ^= true;
			}
			n = (3 * x * x) - (y * y);
			if (x > y && n <= max && n % 12 == 11) {
				sieve[n - min] ^= true;
			}
		}
	}

	//Mark all multiples of squares as non-prime
	for (int i = min; i <= root; i++) {
		if (sieve[i - min]) {
			for (int j = i * i; j < max; j += i * i) {
				sieve[j - min] = false;
			}
		}
	}

	for (int i = max; i > min; i--) {
		if (sieve[i - min]) {
			list = listLink(list, i);
		}
	}

	if (min <= 3) {list = listLink(list, 3);}
	if (min <= 2) {list = listLink(list, 2);}

	return list;
}

// prime generation wrapper
List *genPrimes(int max, int min, List *list) {
	return atkinSievePrimeGen(list, min, max);
}

List *initStack(int num) {
	// calloc sets len/size to 0 and pointer to NULL
	List *list = new List;
	list->link = NULL;
	list->data = 0;
	return list;
}

int freeList(List *list) {
	if (list == NULL) {
		return 1;
	}
	List *next = (List *) list->link;
	delete list;
	return freeList(next);
}

void printList(List *list) {
	if (list == NULL) {
		cout << endl;
	}
	else {
		if (list->data != 0) {
			cout << (int) list->data << ", ";
		}
		printList((List *) list->link);
	}
}

int lenList(List *list) {
	int n;
	if (list == NULL) {
		return 0;
	} else {
		return 1 + lenList((List *) list->link);
	}
}

List *concatList(List *list, List *nlist) {
	if (list->link == NULL) {
		list->link = (void *) nlist;
		return list;
	}
	return concatList((List *) list->link, nlist);
}

List *freeValList(List *list, int n) {
	if (list->data != 0 && list->data < n) {
		return list;
	}
	List *next = (List *) list->link;
	delete list;
	return freeValList(next, n);
}

List *expandList(List *list, int max, int min) {
	// expands list, adding new primes
	List *new_list = initStack(1);
	genPrimes(max, min, new_list);
	concatList(new_list, list);
	return new_list;
}

List *shrinkList(List *list, int max) {
	return freeValList(list, max);
}

#include <limits>

int main() {
	int num = 0;
	int last_num = 1;
	List *primes = initStack(1);
	while (true) {
		cout << "enter max num:\n";
		if (cin >> num) {
			if (num <= 1) {break;}
			cout << "number: " << num << endl;
			if (num > last_num) {
				primes = expandList(primes, num, last_num);
			} else {
				primes = shrinkList(primes, num);
			}
			last_num = num;
			printList(primes);
		} else {
			cout << "err: not a number." << endl;
			cin.clear(); cin.ignore(100, '\n');
		}
	}
	freeList(primes);
	return 0;
}