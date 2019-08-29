#include<iostream>

class Zombie {
	const int speed_;			// not initialized during declaration
	// const field'is initialization done in the constructor

	// constant fields must  be initialized using initializer list
public:
	Zombie(int speed = 0): speed_(speed){		// initialize constant field
	
	}

	int GetSpeed() {
		return speed_;
	}
};

int main() {
	Zombie zombie;
	std::cout << zombie.GetSpeed() << "\n";

	std::cin.get();
}
