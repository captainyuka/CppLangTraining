#include<iostream>

int main() {

	try {
		int* arr = new int[500'000'000];		// try to allocate 500 million elements
		delete[] arr;
	}
	catch (std::bad_alloc) {
		std::cout << "Can not allocate the requested memory...\n";
	}

	std::cout << "Keep going...";

}

