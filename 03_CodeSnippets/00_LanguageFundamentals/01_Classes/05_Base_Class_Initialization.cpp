#include<iostream>

class Fish {
public:
	Fish(bool is_fresh_water): is_fresh_water_(is_fresh_water) {}
	void swim() {
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
	Tuna() : Fish(false) {}	// Constructor initializes the base class
};

class Carp : public Fish {
public:
	Carp() : Fish(true) {}
};	


int main() {
	Carp littleCarp;
	Tuna bigTuna;
	
	std::cout << "Launch: ";
	littleCarp.swim();

	std::cout << "Dinner:";
	bigTuna.swim();

}

