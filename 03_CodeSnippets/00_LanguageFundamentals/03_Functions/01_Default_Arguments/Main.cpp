#include<iostream>

// Even if default argument has not been send, the function works properly by using default argument
void printSum(int x, int y = 0) {
	std::cout << x + y;
}

int main() {
	
	printSum(5,4);
	printSum(5,0);
	printSum(5);

	std::cin.get();
}
