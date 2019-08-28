#include<iostream>

void f(const int x);
const int g();
void f1(int* ptr);
void f2(const int* ptr);

int main() {
	int x = 5;
	const int* ptr = &x;
	//f1(ptr);		// can not pass const int* to a int* param
	int* const ptr2 = &x;
	f1(ptr2);		// we can pass constant pointer

	f2(ptr);		
	f2(ptr2);		// both works

	// For user defined datatypes, returning const, will prevent its modification.

	// Temporary objects created while program execution are always of const type.

	std::cin.get();
}

void f(const int x) {
	//x++;		// Cant increment const int variable
}

// For built in datatypes, returning a const or non-const value, doesn't make any difference.
const int g() {
	// const makes no sense for return values because return values are rvalues in any case and can't be modified.
	return 1;
}

// we cannot pass apointer that points to constant variable(const int*) to this function
// we can pass constant pointer(int* const ptr)
void f1(int* ptr) {}

// we can pass both const int* or int* as argument to this function
void f2(const int* ptr) {}
