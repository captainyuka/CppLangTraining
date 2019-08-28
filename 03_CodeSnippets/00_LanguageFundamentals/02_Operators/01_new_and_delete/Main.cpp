#include<iostream>

void print(int* a) {
	std::cout << *a << std::endl;
}

void printArr(float* arr, int len) {
	for (int i = 0; i < len; i++)
		std::cout << *(arr + i) << " ";
	std::cout << std::endl;
}

class Object {};

int main() {
	
	// Allocate int
	int* x = new int;
	*x = 7;
	print(x);

	// Allocate and init
	int* y = new int(21);
	print(y);

	// Allocate a block of memory
	float* arr = new float[5];
	for (float i = 0.0; i < 5; i++)
		arr[(int)i] = i;
	printArr(arr,5);

	delete x, y;
	delete[] arr;

	/* Every new allocation must be followed by delete operation */
	Object** matrix = new Object*[5];
	for (int i = 0; i < 5; i++)
		matrix[i] = new Object[2];

	for (int i = 0; i < 5; i++)
		delete[] matrix[i];
	delete[] matrix;

	/* If you don't want the new operator throw std::bad_alloc, make it std::nothrow and check the returned pointer if it is nullptr or not */

	int* ptr = new(std::nothrow) int(5);
	if (ptr == nullptr)
		std::cout << "Mememory Allocation Error...\n";
	else
		std::cout << "ptr is " << *ptr;

	std::cin.get();
}
