#include<iostream>

class Zombie {
public:
	static int speed_;
};

int Zombie::speed_ = 2;

int main() {

	
	std::cout << Zombie::speed_;

	std::cin.get();
}