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

typedef unsigned long long _uint;

void error (const char *str) {
	cerr << "Err: " << str << endl;
	exit(1);
}

List *listLink(List *list, _uint item) {
	List *new_list;
	try {
		new_list = new List;
	} catch (std::bad_alloc& ba) {
		error("listLink: new_list did not allocate");
	}
	new_list->data = item;
	new_list->link = NULL;
	list->link = new_list;
	return new_list;
}

List *atkinSievePrimeGen(List *list, _uint min, _uint max) {
	//Create the various different variables required
	int root = ceil(sqrt(max));
	bool *sieve;
	try {
		sieve = new bool[max - min];
	} catch (std::bad_alloc& ba) {
		error("atkinSievePrimeGen: sieve did not allocate");
	}

	for (uint i = 0; i < (max - min); i++) {
		sieve[i] = false;
	}

	for (_uint x = 1; x <= root; x++) {
		for (_uint y = 1; y <= root; y++) {
			_uint n = (4 * x * x) + (y * y);
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

	//Mark all multiples of squares as non-prime
	for (_uint i = min; i <= root; i++) {
		if (sieve[i - min]) {
			for (_uint j = i * i; j < max; j += i * i) {
				sieve[j - min] = false;
			}
		}
	}

	for (_uint i = max; i > min; i--) {
		if (sieve[i - min]) {
			list = listLink(list, i);
		}
	}

	if (min <= 3) {list = listLink(list, 3);}
	if (min <= 2) {list = listLink(list, 2);}

	// free array
	delete[] sieve;

	return list;
}

// prime generation wrapper
List *genPrimes(_uint max, _uint min, List *list) {
	return atkinSievePrimeGen(list, min, max);
}

List *initStack() {
	// calloc sets len/size to 0 and pointer to NULL
	List *list = new List;
	if (list == NULL) {
		error("initStack: init list did not allocate");
	}
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

void print3List(List *list) {
	if (list == NULL) {
		cout << endl;
		return;
	}
	if (list->data != 0) {
		cout << list->data << ", ";
	}
	print3List((List *) list->link);
}

// Iterative print to combat stack overflow
void printList(List *list) {
	//int count = 0;
	for (; list != NULL; list = (List *) list->link) {
		if (list->data != 0) {
			//if(count == 100) {
				cout << list->data << ", ";
				//count = 0;
			//}
			//count++;
		}
	}
	if (list == NULL) {
		cout << endl;
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

List *freeValList(List *list, uint n) {
	if (list->data != 0 && list->data < n) {
		return list;
	}
	List *next = (List *) list->link;
	delete list;
	return freeValList(next, n);
}

List *expandList(List *list, _uint max, _uint min) {
	// expands list, adding new primes
	List *new_list = initStack();
	genPrimes(max, min, new_list);
	concatList(new_list, list);
	return new_list;
}

List *shrinkList(List *list, _uint max) {
	return freeValList(list, max);
}

int main() {
	_uint num = 0;
	_uint last_num = 1;
	List *primes = initStack();
	while (true) {
		cout << "enter max num:\n";
		if (cin >> num) {
			if (num <= 1) {break;}
			cout << "number: " << num << endl;
			if (num > last_num) {
				primes = expandList(primes, num, last_num);
				/*for (int i = (num - last_num) / per_thread; i > 0; i--) {
					primes = expandList(primes, num - (per_thread * i), (num - (per_thread * i)) - per_thread);
					//cout << num - (per_thread * i) << ", " << (num - (per_thread * i)) - per_thread << endl;
				}
				primes = expandList(primes, ((num - last_num) % per_thread) + (num - per_thread), (last_num) + (num - per_thread));
				//cout << ((num - last_num) % per_thread) + (num - per_thread) << ", " << ((last_num) + (num - per_thread)) << endl;
				*/
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