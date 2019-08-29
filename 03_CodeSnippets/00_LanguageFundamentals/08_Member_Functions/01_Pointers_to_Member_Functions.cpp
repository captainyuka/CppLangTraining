#include<iostream>

class Zombie {
	int speed_ = 5;
public: 
	// To have pointer to data member and member functions you need to make them public.
	int GetSpeed() {
		return speed_;
	}

};

int main() {
	
	int (Zombie:: * ptr)();
	ptr = &Zombie::GetSpeed;


	std::cin.get();
}