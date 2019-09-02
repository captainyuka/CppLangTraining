#include<iostream>


int* allocateInt();

int* allocateIntArray(int n);

int main() {
	int* x = allocateInt();
	*x = 5;
	std::cout << x << ":" << *x;
	
	int n = 7;
	int* arr = allocateIntArray(n);
	for (auto i = 0; i < n; ++i)
		* (arr + i) = i;
	for (auto i = 0; i < n; ++i)
		std::cout << arr[i] << '\n';

	
	delete[] arr;
	delete x;
}

int* allocateInt() {
	int* x = new int;
	return x;
}

int* allocateIntArray(int n = 1) {
	int* arr = new int[n];
	return arr;
}

