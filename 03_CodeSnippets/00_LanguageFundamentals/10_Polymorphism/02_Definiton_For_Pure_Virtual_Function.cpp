#include<iostream>

class Person {		// Abstract class
	// Classes that has one or more Pure Virtual Function is called Abstract Classes and can not be instantiated
	public:
		virtual void work() = 0;		// Pure Virtual Function
};

// Small Definition for Pure Virtual Function
// Can not be defined inside class
void Person::work() {
	// All derived classes should start working by first doing this function
	std::cout << "Bismillah\n";	
}

class SoftwareEngineer : public Person {
	void work() {
		Person::work();						// Non-virtual call ~ syntax 1
		std::cout << "Coding...\n";
	}
};

class Architect : public Person {
	void work() {
		this->Person::work();				// Non-virtual call ~ syntax 2
		std::cout << "Modeling...\n";
	}
};

int main() {
    // We can create pointer or reference of abstract classes
	Person* person;		
	SoftwareEngineer x;
	person = &x;
	person->work();
	
	std::cout << '\n';

	Person& person2 = x;
	person2.work();

	std::cout << '\n';

	Architect architect;
	Person& person3 = architect;
	person3.work();
	
	architect.Person::work();				// Non-virtual call ~ syntax 3


	std::cin.get();

}