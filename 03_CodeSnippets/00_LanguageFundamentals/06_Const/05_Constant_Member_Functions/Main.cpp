#include<iostream>

class Zombie {
	int speed_ = 5;
public:

	// A const member function never modifies data members in an object.
	void doSomethings() const {
		//	speed_ = 7;		// Can not change any field

		// We can do anything else but changing fields

		// 'this' passed to this method as const so as we can not change any fields of const object
		// we cannot change field of 'this' since passed as const
	}
};

int main() {
	Zombie zombie;
	
	
	std::cin.get();
}
