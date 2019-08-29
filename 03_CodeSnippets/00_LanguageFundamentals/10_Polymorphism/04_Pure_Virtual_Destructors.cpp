#include<iostream>

class Animal {
	public:
		virtual ~Animal() = 0;

	// pure virtual destructor will make its Base class Abstract, hence you cannot create object of that class.
};

// Definition for Pure Virtual Destructor
 Animal::~Animal() {
	 // Pure Virtual Destructors must be defined
	std::cout << "Animal Destructor...\n";
}


class Bird : public Animal {
	public:
		~Bird() {
			std::cout << "Bird Destructor...\n";
		}
	// There is no requirement of implementing pure virtual destructors in the derived classes.	
};

int main(){

	Animal* animal = new Bird;				// Upcasting
	delete animal;							// No memory leak

	std::cin.get();
}