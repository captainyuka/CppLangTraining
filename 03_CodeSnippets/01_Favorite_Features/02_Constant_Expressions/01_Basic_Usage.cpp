#include<iostream>
	
// Only use for true constants
constexpr double GetPi() { return 22.0 / 7; }

// Compile-time resolution of TwicePi() increases the speed 
constexpr double TwicePi() { return 2 * GetPi(); }

int main(){
	// The compiler substituted every usage of GetPi() by 3.14286 and every usage of TwicePi() by 6.28571
	std::cout << "Pi: " << GetPi() << '\n';
	std::cout << "Twice Of Pi: " << TwicePi() << '\n';

	/**
	 * if you use a constexpr expression to double a user provided number. 
	 * The outcome of such an expression cannot be calculated by the compiler, 
	 * which may ignore the usage of constexpr and compile as a regular function.
	 */

	std::cin.get();
}

