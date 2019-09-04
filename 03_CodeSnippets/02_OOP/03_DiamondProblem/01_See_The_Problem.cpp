#include<iostream>

class Animal {
public:
	int age;

	Animal() {
		std::cout << "Animal Constructed\n";
	}
};

class Mammal : public Animal {

};

class Bird : public Animal {

};

class Reptile : public Animal {

};

class Platypus final : public Mammal, public Bird, public Reptile {
public:
	Platypus() {
		std::cout << "Platypus Constructed\n";
	}
};
int main() {
	Platypus p;		// Oddly three animal constructed
	//p.age = 5;	// compiler doesn't know which animal instance's age we are referring to

}