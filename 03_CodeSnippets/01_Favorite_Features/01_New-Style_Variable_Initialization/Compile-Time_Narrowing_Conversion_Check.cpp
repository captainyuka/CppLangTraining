#include<iostream>
#include<cstdint>

int main(){

	long p{50000000};		// init p with given value, if flows, give error

	// This tyle checks narrowing conversion and gives compile time error

	short x{p};					// Error, requires narrowing conversion
	int y{ p };					// Error, "	
	short x{ 5000 };			// Error, "	

	long long s{ p };			// No Eror

	std::cin.get();
}

