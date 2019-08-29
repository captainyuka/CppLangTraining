#include<iostream>

class Animal {
public: 
	int legs_ = 4;

	Animal() {
		std::cout << "Hi From Animal Constructor...\n";
	}

	Animal(int legs) {
		this->legs_ = legs;
		std::cout << "Hi From Parameterized Animal Constructor...\n";
	}

	void move() {
		std::cout << "Animal is moving\n";
	}
};

class Cat : public Animal {
public:
	float tail_length_ = 0.0f;
	int age_ = 0;

	Cat(){
		std::cout << "Hi From Cat Constructor...\n";
	}

	Cat(float tail_length, int age) {
		this->tail_length_ = tail_length;
		this->age_ = age;
		std::cout << "Hi From Parameterized Cat Constructor...\n";
	}
	
};

class Snake : public Animal {
public:
	Snake(): Animal(0){		// call parameterized constructor of superclass
		std::cout << "Hi From Default Snake Constructor...\n";
	}
};

int main() {
	Cat kitty;
	std::cout << "\n";

	Cat* cat = new Cat(0.7f,3);
	std::cout << "\n";
	// Whether derived class's default constructor is called or parameterised is called, 
	// base class's default constructor is always called inside them.
	
	Snake snake;
	std::cout << "\n";

	std::cin.get();
}