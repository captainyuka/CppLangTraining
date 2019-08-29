#include<iostream>


int& f();
void f2(const int& x);

int main() {
	int x = 5;
	int y = 10;
	// int& ref;		// references must be initialized when it is declared.
	
	// References are like constant pointers that are automatically dereferenced.
	int& ref = y;	// ref to y
	
	// Once initialized, we can not change references

	// We can never have NULL reference
	
	// Be careful with scopes
	int& p = f();		// Cause of error when activity record in stack is reused...
	
	// values of const references can not be changed
	f2(y);

	std::cin.get();
}

int& f() {
	int x;
	return x;		// scope of x ends
}

void f2(const int& x) {
	// x++;		// can not change const reference
}

