#include<iostream>

class Zombie {
public:
	static void f() {
		// implementation
	}

};


int main() {

	Zombie zombie;
	zombie.f();			// you can call by using dot notation

	Zombie::f();		// but it is typically called by using scope resolution(::) operator

	std::cin.get();
}