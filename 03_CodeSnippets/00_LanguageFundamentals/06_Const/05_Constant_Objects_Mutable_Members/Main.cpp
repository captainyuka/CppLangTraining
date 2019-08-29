#include<iostream>

class Zombie {
public:
	mutable	int speed_ = 5;		// mutable data members of a const objects can be modified.

};

int main() {
	const Zombie zombie;			// we can not change any of its fields but mutable ones
	
	zombie.speed_ = 7;		// since speed_ is mutable field, change is possible

	std::cout << zombie.speed_ << "\n";
	
	std::cin.get();
}
