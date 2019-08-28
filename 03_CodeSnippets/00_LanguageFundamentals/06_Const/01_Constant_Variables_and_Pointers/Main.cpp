#include<iostream>


int main() {
	
	/* Constant Variable */
	const int x = 5;			// You need to initialize when you declare the const variable
	std::cout << x << "\n";

	/* Pointer to Constant Variable */
	const int* y;				// y is a pointer that points to const int type
	y = &x;						// initialize
	
	// We can't change the value y points to since it points to a const int
	//*y = 5;					
	
	// But we can change where the y points to since pointer is not constant, what it points to is a constant
	const int temp = 7;
	y = &temp;	

	int const* sameAsY;
	sameAsY = &x;

	//*sameAsY = 5;		// can't change const int which the sameAsY points to
	sameAsY = &temp;	// we can change the pointer since it is not constant but what it points to is a constant


	/* Constant Pointers */

	// !! To make a pointer constant, we have to put the const keyword to the right of the *
	int p = 8;
	int* const constantPointer = &p;			// we need to initialize while compiling
	++*constantPointer;
	std::cout << "As we see we can change what the constant pointer points to but not the pointer itself... p: " << *constantPointer << "\n";
	int px = 7;
	// constantPointer = &px;			// cant change the pointer
	
	/* Constant Pointer Which Points to Constant Variable */
	const char h = 'h';
	const char* normalPtrToConstChar = &h;
	const char* const constPtrToConstChar = &h;
	
	const char b = 'b';
	normalPtrToConstChar = &b;			// we can change this one
//	constPtrToConstChar = &b;			// we can change this one is const pointer change the pointer itself
//	*constPtrToConstChar = 'p';			// we can't change its content either since it points to a const char


	std::cin.get();
}