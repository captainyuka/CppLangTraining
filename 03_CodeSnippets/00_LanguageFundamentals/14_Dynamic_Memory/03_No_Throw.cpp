#include<iostream>

int main() {

	int* const ptr = new(std::nothrow) int[500'000'000];	// Allocate 500 million integers
	if (ptr == nullptr)
		std::cout << "Can not allocate the requested memory...\n";

	if( !ptr )
		std::cout << "2 Can not allocate the requested memory...\n";


	std::cout << "Keep going...";
	
	if (ptr != nullptr)
		delete[] ptr;
}

