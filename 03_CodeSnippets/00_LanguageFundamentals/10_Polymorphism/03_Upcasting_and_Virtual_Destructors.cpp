#include<iostream>

class Person {	
	
	public:
		~Person() {
			std::cout << "Person Destructor...\n";
		}
};

class Architect : public Person {
	public:
		~Architect() {
			std::cout << "Architect Destructor...\n";
		}
};

class Animal {
	public:
		/*
		 * Using virtual Destructors Ensures That 
		 * Destructors in Derived Classes Are Invoked 
		 * When Deleting a Pointer of Type Base* 
	   	 */
		virtual ~Animal() {
			std::cout << "Animal Destructor...\n";
		}
};

class Bird : public Animal {
	public:
		~Bird() {
			std::cout << "Bird Destructor...\n";
		}
};

int main(){

	Person* person = new Architect;			// Upcasting
	delete person;			// Just calls Person destructor, Results in memory leak....
	
	std::cout << '\n';

	Animal* animal = new Bird;				// Upcasting
	delete animal;			// No memory leak with the help of virtual destructor

	std::cin.get();
}