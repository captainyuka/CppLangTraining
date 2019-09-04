#include<iostream>

class Fish {
public:
	Fish(bool is_fresh_water): is_fresh_water_(is_fresh_water) {}
	void Swim() {
		if (is_fresh_water_)
			std::cout << "Swimming in lake\n";
		else
			std::cout << "Swimming in sea\n";
	}
	// Overloaded Swim
	void Swim(bool is_fresh_water) {	
		if (is_fresh_water_)
			std::cout << "Swimming in lake\n";
		else
			std::cout << "Swimming in sea\n";
	}
private:
	bool is_fresh_water_;
};

class Tuna : public Fish {
public:
	using Fish::Swim;
	Tuna() : Fish(false) {}	// Constructor initializes the base class
	void Swim() {
		std::cout << "Tuna swims really fast\n";
		Fish::Swim();
	}
};

class Carp : public Fish {
public:
	using Fish::Swim;
	Carp() : Fish(true) {}
	void Swim() {
		std::cout << "Carp swims kinda slowly\n";
		Fish::Swim();
	}
};	


int main() {
	Carp littleCarp;
	Tuna bigTuna;
	
	std::cout << "Launch: ";
	littleCarp.Swim();

	std::cout << "Dinner:";
	bigTuna.Swim();

	// Since subclass implements its own version of Swim, all overloaded parent class methods of swim will be hidden
	// Uncomment using Fish::Swim() line in class declearation to unhide them
	// bigTuna.Swim(true);	
}

