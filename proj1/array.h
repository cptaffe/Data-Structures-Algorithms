// CPSC2380
// Department of Computer Science, UALR
// Project 1
// Student Name: Connor Taffe
// Student UALR ID (last four digits): 3742
// Project Descriptions: (maximum 5 lines)
// This project is doing dynamic array expansion for storage of prime numbers.
// Project Due Date: 28/8/2014
// Project Revised Date: 4/9/2014

#include <iostream>

using namespace std;

typedef struct {
	int *nums; // integer array
	int len; // length of size filled
	int size; // allocated size
} Array;

int *IntArrayCopy(int *arr, int *old, int len) {
	for (int i = 0; i < len; i++) {
		arr[i] = old[i];
	}
	return arr;
}

Array* ArrayExpand(Array *array) {
	int *new_array;
	if (array->nums != NULL) {
		const int size = (array->size * 2) + 1;
		new_array = new int[size];
		array->size = size;
		IntArrayCopy(new_array, array->nums, array->len);
		delete[] array->nums;
	} else {
		new_array = new int[3];
		array->size = 3;
	}
	array->nums = new_array;
	return array;
}

Array *ArrayPush(Array *array, int num) {
	if (array->len >= array->size) {
		ArrayExpand(array);
	}
	array->nums[array->len] = num; array->len++;
	return array;
}

void ArrayPrint(Array *array) {
	if (array->len == 0) {cout << "No primes found." << endl; return;}
	for (int i = array->len - 1; i >= 0; i--) {
		cout << array->nums[i] << ", ";
	}
	cout << endl;
}

Array *ArrayIndexlt(Array *array, int n) {
	for (int j = 0; j < array->len; j++) {
		if (array->nums[j] > n) {
			array->size = array->len = j;
			array->nums = (int *) realloc(array->nums, array->size * sizeof (int));
			return array;
		}
	}
	return array;
}