#include<iostream>

void printSum(int x, int = 0);		// Function with Placeholder Arguments, declared here defined somewhere else

void print(int x, int y = 0) {		// Function with Default Arguments
	printSum(x, y);
}

int main() {

	print(5, 4);
	print(5, 0);
	print(5);

	// 1- Only the last argument must be given default value. 
	//		You cannot have a default argument followed by non-default argument.

	// 2 - If you default an argument, then you will have to default all the subsequent arguments after that.
	
	// 3 - Even if default argument has not been send, the function works properly by using default argument


	std::cin.get();
}

// Functinos that uses Placeholder Arguments should not redeclare itself as in here (int x, int y = 0) 
void printSum(int x, int y) {
	std::cout << x + y;
}