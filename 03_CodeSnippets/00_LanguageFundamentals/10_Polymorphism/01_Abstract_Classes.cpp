#include<iostream>

class Person {		// Abstract class
	// Classes that has one or more Pure Virtual Function is called Abstract Classes and can not be instantiated
	public:
		virtual void work() = 0;		// Pure Virtual Function
};

class SoftwareEngineer : public Person {
	void work() {
		std::cout << "Coding...\n";
	}
};

int main() {
    // We can create pointer or reference of abstract classes
	Person* person;		
	SoftwareEngineer x;
	person = &x;
	person->work();

	Person& person2 = x;
	person2.work();

	std::cin.get();
}