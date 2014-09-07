// CPSC2380
// Department of Computer Science, UALR
// Project 1
// Student Name: Connor Taffe
// Student UALR ID (last four digits): 3742
// Project Descriptions: (maximum 5 lines)
// This project is doing dynamic array expansion for storage of prime numbers.
// Project Due Date: 28/8/2014
// Project Revised Date: 4/9/2014

#include "prime.h"
#include "array.h"

using namespace std;

int main() {
	Array arr;
	arr.nums = NULL;
	arr.len = 0;
	arr.size = 0;
	int num, old;
	num = 0; old = 0;
	// reads input in loop until <= 0 is typed.
	while (true) {
		cout << "Input number" << endl;
		if (cin >> num) {
			if (num <= 0) {break;}
			if (num < old) {
				arr = *ArrayIndexlt(&arr, num);
			} else {
				PrimeGen(&arr, old, num);
			}
			ArrayPrint(&arr);
			old = num;
		} else {
			cout << "not a number" << endl;
			break;
		}
	}
	if (arr.nums != NULL) {
		delete[] arr.nums;
	}
	return 0;
}