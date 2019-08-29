#include<iostream>

class Zombie {
public:
	int speed_ = 5;
};

int main() {
	const Zombie zombie;
	std::cout << zombie.speed_ << "\n";

	// 	zombie.speed_ = -5; // Cannot assign to a const object
	std::cout << zombie.speed_ << "\n";
	
	std::cin.get();
}
